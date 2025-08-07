//
//  RNBOController.swift
//  SwiftUI_RNBO_FromScratch_Test
//
//  Created by Eldar Sadykov on 13.02.2023.
//

import Foundation

struct ParameterConfig: Codable {
    let id: String
    var displayName: String
    var visible: Bool
}

typealias RNBOContext = RNBOAudioUnitHostModel

extension RNBOAudioUnitHostModel {
    /// Biedt de AVAudioUnit-node voor MIDI-routing
    func getAVAudioUnitNode() -> AVAudioUnit? {
        return audioEngine.getAVAudioUnitNode()
    }
}

extension RNBOAudioUnitHostModel {
    
    private var configFileName: String { "parameterConfig" }
    
    static func loadParameterConfiguration(
        from parameters: [RNBOParameter],
        configFileName: String = "parameterConfig"
    ) -> [ParameterConfig] {
        guard let configURL = Bundle.main.url(forResource: configFileName, withExtension: "json") else {
            printExampleParameterConfig(parameters: parameters)
            return parameters.map {
                ParameterConfig(id: $0.id, displayName: $0.info.name, visible: true)
            }
        }

        do {
            let data = try Data(contentsOf: configURL)
            let loadedConfigs = try JSONDecoder().decode([ParameterConfig].self, from: data)
            return loadedConfigs
        } catch {
            print("Error loading parameter config: \(error)")
            printExampleParameterConfig(parameters: parameters)
            return parameters.map {
                ParameterConfig(id: $0.id, displayName: $0.info.name, visible: true)
            }
        }
    }

    static func printExampleParameterConfig(parameters: [RNBOParameter]) {
        let exampleConfig = parameters.map {
            ParameterConfig(id: $0.id, displayName: $0.info.name, visible: true)
        }
        do {
            let encoder = JSONEncoder()
            encoder.outputFormatting = [.prettyPrinted, .sortedKeys]
            let jsonData = try encoder.encode(exampleConfig)
            let jsonString = String(data: jsonData, encoding: .utf8)!
            print("""
            === Example parameterConfig.json ===
            \(jsonString)
            ====================================
            """)
        } catch {
            print("Failed to encode example config: \(error)")
        }
    }
}

class RNBOAudioUnitHostModel: ObservableObject {
    
    private let audioEngine = RNBOAudioEngine()
    private var _audioUnit: RNBOAudioUnit!
    public var audioUnit: RNBOAudioUnit {
        _audioUnit
    }
    private let eventHandler = RNBOEventHandler()
    @Published var parameters: [RNBOParameter]
    @Published var parameterConfigs: [ParameterConfig]
    @Published var showDescription: Bool = false
    @Published var currentOctave: Int = 0
    @Published private(set) var activeMIDINotes: Set<UInt8> = []

    let description: RNBODescription?
    
    init() {
        do {
            let url = Bundle.main.url(forResource: "description", withExtension: "json")!
            let data = try Data(contentsOf: url)
            description = try JSONDecoder().decode(RNBODescription.self, from: data)
        } catch {
            print("Error decoding JSON from URL: \(error)")
            description = nil
        }
        
        _audioUnit = audioEngine.getAudioUnit()
        let localParameters = description?.getParametersArray() ?? []
        self.parameters = localParameters
        self.parameterConfigs = Self.loadParameterConfiguration(from: localParameters)
    }

    func playAudioFile() {
        audioEngine.playAudioFile()
    }
    
    func pauseAudioFile() {
        audioEngine.pauseAudioFile()
    }

    func toggleMic(_ on: Bool) {
        if on {
            audioEngine.setMicrophoneAmplitude(1.0)
        } else {
            audioEngine.setMicrophoneAmplitude(0.0)
        }
    }

    func refreshParameterValue(at parameterIndex: Int) {
        parameters[parameterIndex].value = Double(audioUnit.getParameterValue(parameterIndex))
    }

    func setParameterValue(to value: Double, at parameterIndex: Int) {
        audioUnit.setParameterValue(parameterIndex, value: Float(value))
    }

    func setParameterValueHot(to value: Double, at parameterIndex: Int) {
        setParameterValue(to: value, at: parameterIndex)
        refreshParameterValue(at: parameterIndex)
    }

    func setParameterValueNormalized(to valueNormalized: Double, at parameterIndex: Int) {
        audioUnit.setParameterValueNormalized(parameterIndex, valueNormalized: Float(valueNormalized))
    }

    func setParameterValueNormalizedHot(to valueNormalized: Double, at parameterIndex: Int) {
        setParameterValueNormalized(to: valueNormalized, at: parameterIndex)
        refreshParameterValue(at: parameterIndex)
    }

    func sendMessage(_ message: [Double]) {
        audioUnit.sendMessage("foo", list: message)
    }

    func sendNoteOn(_ pitch: UInt8, velocity: UInt8 = 127, channel: UInt8 = 0) {
        let transposedPitch = UInt8(Int(pitch) + currentOctave * 12)
        audioUnit.sendNoteOnMessage(withPitch: transposedPitch, velocity: velocity, channel: channel)
        activeMIDINotes.insert(transposedPitch)
    }

    func sendNoteOff(_ pitch: UInt8, releaseVelocity: UInt8 = 0, channel: UInt8 = 0) {
        let transposedPitch = UInt8(Int(pitch) + currentOctave * 12)
        audioUnit.sendNoteOffMessage(withPitch: transposedPitch, releaseVelocity: releaseVelocity, channel: channel)
        activeMIDINotes.remove(transposedPitch)
    }
    
    func sendAllNotesOff(channel: UInt8 = 0) {
        for pitch in activeMIDINotes {
            audioUnit.sendNoteOffMessage(withPitch: pitch, releaseVelocity: 0, channel: channel)
        }
        activeMIDINotes.removeAll()
    }

    func sendAftertouch(_ pitch: UInt8, pressure: UInt8, channel: UInt8 = 0) {
        audioUnit.sendAftertouchMessage(withPitch: pitch, pressure: pressure, channel: channel)
    }

    func sendContinuousController(_ number: UInt8, value: UInt8, channel: UInt8 = 0) {
        audioUnit.sendContinuousController(withNumber: number, value: value, channel: channel)
    }

    func sendPatchChange(_ program: UInt8, channel: UInt8 = 0) {
        audioUnit.sendPatchChangeMessage(withProgram: program, channel: channel)
    }

    func sendChannelPressure(_ pressure: UInt8, channel: UInt8 = 0) {
        audioUnit.sendChannelPressureMessage(withPressure: pressure, channel: channel)
    }

    func sendPitchBend(_ value: UInt16, channel: UInt8 = 0) {
        audioUnit.sendPitchBendMessage(withValue: value, channel: channel)
    }

    func connectEventHandler() {
        audioUnit.setEventHandler(eventHandler)
        eventHandler.rnbo = self
    }
}
