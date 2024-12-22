//
//  AudioEngine.swift
//  RNBO_AVAudioEngine
//
//  Created by Alex Nadzharov on 13.02.2023.
//

import AVFoundation

class RNBOAudioEngine {
    private let engine = AVAudioEngine()
    private var avAudioUnit: AVAudioUnit?
    private let playerNode = AVAudioPlayerNode()
    private let audioFile: AVAudioFile?
    private let distortionEffect: AVAudioUnitDistortion
    private let inputMixer: AVAudioMixerNode
    private let microphoneVolumeMixer: AVAudioMixerNode
    
    private func initInput() {
        guard let avAudioUnit = avAudioUnit else {
            print("AVAudioUnit is not initialized")
            return
        }
        
        let input = engine.inputNode
        let inputFormat = input.outputFormat(forBus: 0)
        let targetFormat = avAudioUnit.inputFormat(forBus: 0)
        
        print("Input node sample rate: \(inputFormat.sampleRate)")
        print("AVAudioUnit sample rate: \(targetFormat.sampleRate)")

        // Verbinden met AVAudioEngine's automatische conversie
        engine.connect(input, to: microphoneVolumeMixer, format: inputFormat)
        engine.connect(microphoneVolumeMixer, to: inputMixer, format: nil) // Laat AVAudioEngine het formaat bepalen
        engine.connect(inputMixer, to: avAudioUnit, format: targetFormat)
    }

    func setMicrophoneAmplitude(_ amp: Float) {
        microphoneVolumeMixer.outputVolume = amp
    }

    init() {
        inputMixer = AVAudioMixerNode()
        microphoneVolumeMixer = AVAudioMixerNode()
        distortionEffect = AVAudioUnitDistortion()
        distortionEffect.loadFactoryPreset(.multiEcho1)
        
        // Stel de voorkeurssample rate in
        #if os(iOS)
            do {
                let session = AVAudioSession.sharedInstance()
                try session.setCategory(.playAndRecord, options: [.defaultToSpeaker, .allowBluetoothA2DP, .mixWithOthers, .allowAirPlay])
                try session.setPreferredSampleRate(44100) // Stel de voorkeurssample rate in op 44100 Hz
                try session.setActive(true)
                
                // Controleer de daadwerkelijke sample rate
                let actualSampleRate = session.sampleRate
                print("Actual sample rate after setup: \(actualSampleRate)")
            } catch {
                print("Error setting up audio session: \(error.localizedDescription)")
            }
        #endif
        
        // Initialiseer het audiobestand
        if let audioFileURL = Bundle.main.url(forResource: "Synth", withExtension: "aif") {
            do {
                audioFile = try AVAudioFile(forReading: audioFileURL)
            } catch {
                print("Error initializing audio file: \(error)")
                audioFile = nil
            }
        } else {
            print("Audio file not found")
            audioFile = nil
        }

        // Definieer de AudioComponentDescription
        let type = kAudioUnitType_Effect
        let subType: OSType = 0x71717171
        let manufacturer: OSType = 0x70707070
        let description = AudioComponentDescription(componentType: type, componentSubType: subType, componentManufacturer: manufacturer, componentFlags: 0, componentFlagsMask: 0)

        let subclass = RNBOAudioUnit.self

        // Registreer de AVAudioUnit subclass
        AUAudioUnit.registerSubclass(subclass, as: description, name: "RNBOAudioUnit", version: 1)

        // Instantiate de AVAudioUnit
        AVAudioUnit.instantiate(with: description, options: AudioComponentInstantiationOptions.loadOutOfProcess) { [weak self] avAudioUnit, error in
            guard let self = self else { return }
            if let error = error {
                print("Error instantiating AVAudioUnit: \(error.localizedDescription)")
                return
            }
            guard let avAudioUnit = avAudioUnit else {
                print("Failed to instantiate AVAudioUnit")
                return
            }
            self.avAudioUnit = avAudioUnit

            // Attach de nodes aan de audio-engine
            self.engine.attach(self.inputMixer)
            self.engine.attach(self.microphoneVolumeMixer)
            self.engine.attach(self.playerNode)
            self.engine.attach(self.avAudioUnit!)
            
            self.microphoneVolumeMixer.outputVolume = 0.0

            // Vraag om microfoon permissie indien nodig
            switch AVCaptureDevice.authorizationStatus(for: .audio) {
            case .authorized:
                print("Inputs: authorized")
                self.initInput()
            case .notDetermined:
                print("Inputs: not determined")
                AVCaptureDevice.requestAccess(for: .audio) { granted in
                    if granted {
                        self.initInput()
                    } else {
                        print("Microfoon toegang geweigerd")
                    }
                }
            case .denied:
                print("Inputs: denied")
            case .restricted:
                print("Inputs: restricted")
            @unknown default:
                print("Inputs: unknown status")
            }

            // Controleer de sample rates opnieuw
            let inputFormat = self.avAudioUnit!.inputFormat(forBus: 0)
            let playerFormat = self.playerNode.outputFormat(forBus: 0)
            print("Player node sample rate: \(playerFormat.sampleRate)")
            print("AVAudioUnit sample rate: \(inputFormat.sampleRate)")

            // Connect de playerNode naar de inputMixer met dezelfde sample rate
            self.engine.connect(self.playerNode, to: self.inputMixer, format: inputFormat)
            self.engine.connect(self.avAudioUnit!, to: self.engine.mainMixerNode, format: inputFormat)

            // Connect de mainMixerNode naar de outputNode
            let outputFormat = self.engine.outputNode.inputFormat(forBus: 0)
            self.engine.connect(self.engine.mainMixerNode, to: self.engine.outputNode, format: outputFormat)

            // Voorbereiden en starten van de engine
            self.engine.prepare()
            do {
                try self.engine.start()
                print("AVAudioEngine gestart")
            } catch {
                print("Failed to start AVAudioEngine: \(error.localizedDescription)")
            }
        }
    }

    func getAudioUnit() -> RNBOAudioUnit {
        return avAudioUnit!.auAudioUnit as! RNBOAudioUnit
    }

    func playAudioFile() {
        playerNode.stop()
        guard let audioFile = audioFile else {
            return
        }

        playerNode.rate = 1
        playerNode.scheduleFile(audioFile, at: nil) {
            print("Audio playback finished")
        }

        playerNode.play()
    }

    func pauseAudioFile() {
        playerNode.pause()
    }
}
