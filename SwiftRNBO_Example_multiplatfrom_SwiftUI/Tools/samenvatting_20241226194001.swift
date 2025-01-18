//Bestand: AudioKitKeyboard.swift
    struct AudioKitKeyboard: View {
        @EnvironmentObject var rnbo: RNBOAudioUnitHostModel
        @State private var latch = false
        var body: some View {
            VStack {
                HStack {
                    Toggle(isOn: $latch) {
                        Text("Latch keys")
                    }
                    Spacer()
                }
                Keyboard(latching: latch) { pitch, point in
                    let pitch = UInt8(pitch.midiNoteNumber)
                    let velocity = latch ? 60 : UInt8(point.y * 127)
                    rnbo.sendNoteOn(pitch, velocity: velocity)
                } noteOff: { pitch in
                    let pitch = UInt8(pitch.midiNoteNumber)
                    rnbo.sendNoteOff(pitch)
                }
                .frame(height: 100)
                .frame(minWidth: 600)
            }
        }
    }

//Bestand: Buttons.swift
struct Buttons: View {
    @EnvironmentObject var rnbo: RNBOAudioUnitHostModel
    @State private var enableMic: Bool = false
    var body: some View {
        HStack {
            Button("Test MIDI") {
                print("CC")
                rnbo.sendContinuousController(11, value: 60)
                print("PitchBend")
                rnbo.sendPitchBend(8192)
                print("Patch")
                rnbo.sendPatchChange(1)
                print("Pressure")
                rnbo.sendChannelPressure(60)
                print("Aftertouch")
                rnbo.sendAftertouch(60, pressure: 50)
            }
            Button("Randomize") {
                randomize()
            }
            Button("Send message") {
                let message: [Double] = [220, 330, 0.2, 0.3, 0.5]
                rnbo.sendMessage(message)
            }
            Button("Play Input") {
                rnbo.playAudioFile()
            }
            Button("Pause Input") {
                rnbo.pauseAudioFile()
            }
            Toggle(isOn: $rnbo.showDescription) {
                Text("Show description")
            }
            Toggle(isOn: $enableMic) {
                Text("Mic")
            }
            .onChange(of: enableMic) { newValue in
                rnbo.toggleMic(newValue)
            }
        }
        .padding(.bottom)
    }

    fileprivate func randomize() {
        for i in rnbo.parameters.indices {
            rnbo.setParameterValueNormalizedHot(to: Double.random(in: 0 ... 1), at: i)
        }
    }
}

//Bestand: SwiftRNBO_Example_multiplatfrom_SwiftUIApp.swift
struct SwiftRNBO_Example_multiplatfrom_SwiftUIApp: App {
    @ObservedObject var rnbo = RNBOAudioUnitHostModel()
    var body: some Scene {
        WindowGroup {
            ContentView()
                .onAppear { rnbo.connectEventHandler() }
                .environmentObject(rnbo)
        }
    }
}

//Bestand: Sliders.swift
    struct Sliders: View {
        @EnvironmentObject var rnbo: RNBOAudioUnitHostModel

        var body: some View {
            ScrollView {
                VStack {
                    ForEach($rnbo.parameters) { $parameter in
                        SliderView(parameter: $parameter)
                    }
                }
                .padding()
                .background()
                .padding(.bottom)
            }
            .frame(minHeight: 100)
            .padding(.bottom)
        }
    }
    struct SliderValueLabel: View {
        let value: Double
        var body: some View {
            Text(String(format: "%.2f", value))
                .frame(minWidth: 50)
        }
    }
    struct SliderNameLabel: View {
        let name: String
        var body: some View {
            Text(name)
                .frame(minWidth: 100)
        }
    }

//Bestand: SliderView.swift
struct SliderView: View {
    @EnvironmentObject var rnbo: RNBOAudioUnitHostModel
    @Binding var parameter: RNBOParameter
    var body: some View {
        HStack {
//            let displayName = parameter.displayName != "" ? parameter.displayName : parameter.name.capitalizedSentence
            let displayName = parameter.info.paramId
            #if os(iOS)
                SliderNameLabel(name: displayName)
            #endif
            Slider(value: $parameter.valueNormalized) {
                SliderNameLabel(name: displayName)
            } minimumValueLabel: {
                SliderValueLabel(value: parameter.info.minimum)
            } maximumValueLabel: {
                SliderValueLabel(value: parameter.info.maximum)
            }
            .onChange(of: parameter.valueNormalized) { rnbo.setParameterValueNormalized(to: $0, at: parameter.info.index) }
            SliderValueLabel(value: parameter.value)
        }
    }
}

//Bestand: ContentView.swift
struct ContentView: View {
    @EnvironmentObject var rnbo: RNBOAudioUnitHostModel

    var body: some View {
        VStack(spacing: 0) {
            Buttons()
            #if !os(tvOS)
                if rnbo.showDescription {
                    DescriptionView()
                } else {
                    Sliders()
                    AudioKitKeyboard()
                }
            #endif
        }
        .padding()
    }
}

//Bestand: DescriptionView.swift
    struct DescriptionView: View {
        @EnvironmentObject var rnbo: RNBOAudioUnitHostModel

        var body: some View {
            Group {
                if let rnboDescription = rnbo.description {
                    List {
                        Section(header: Text("Parameters")) {
                            if !rnboDescription.parameters.isEmpty {
                                ForEach(rnboDescription.parameters) { parameter in
//                                    let groupTitle = parameter.displayName == "" ? parameter.name : parameter.displayName
                                    DisclosureGroup("\(parameter.index): \(parameter.paramId)") {
                                        ParameterView(parameter: parameter)
                                    }
                                }
                            }
                        }

                        Section(header: Text("External Data Refs")) {
                            if !rnboDescription.externalDataRefs.isEmpty {
                                ForEach(rnboDescription.externalDataRefs, id: \.id) { ref in
                                    ExternalDataRefView(ref: ref)
                                }
                            }
                        }

                        Section(header: Text("Inports")) {
                            if !rnboDescription.inports.isEmpty {
                                ForEach(rnboDescription.inports, id: \.tag) { port in
                                    PortView(port: port)
                                }
                            }
                        }

                        Section(header: Text("Outports")) {
                            if !rnboDescription.outports.isEmpty {
                                ForEach(rnboDescription.outports, id: \.tag) { port in
                                    PortView(port: port)
                                }
                            }
                        }

                        Section(header: Text("Inlets")) {
                            if !rnboDescription.inlets.isEmpty {
                                ForEach(rnboDescription.inlets.indices, id: \.self) { index in
                                    InletOutletView(inletOutlet: rnboDescription.inlets[index])
                                }
                            }
                        }

                        Section(header: Text("Outlets")) {
                            if !rnboDescription.outlets.isEmpty {
                                ForEach(rnboDescription.outlets.indices, id: \.self) { index in
                                    InletOutletView(inletOutlet: rnboDescription.outlets[index])
                                }
                            }
                        }

                        Section(header: Text("Meta")) {
                            MetaView(meta: rnboDescription.meta)
                        }
                    }
                    .frame(minHeight: 100)
                } else {
                    Text("Error loading description")
                        .padding()
                        .background()
                }
            }

            .padding(.bottom)
        }
    }
    struct ParameterView: View {
        let parameter: ParameterInfo

        var body: some View {
            Text("Name: \(parameter.name)")
            Text("ID: \(parameter.paramId)")
            Text("Minimum Value: \(parameter.minimum)")
            Text("Maximum Value: \(parameter.maximum)")
            Text("Exponent: \(parameter.exponent)")
            Text("Steps: \(parameter.steps)")
            Text("Initial Value: \(parameter.initialValue)")
            Text("Is Enum: \(parameter.isEnum ? "Yes" : "No")")
            if parameter.isEnum {
                Text("Enum Values: \(parameter.enumValues.map { $0.string }.joined(separator: ", "))")
            }
            Text("Display Name: \(parameter.displayName)")
            Text("Unit: \(parameter.unit)")
            Text("Order: \(parameter.order)")
            Text("Debug: \(parameter.debug ? "Yes" : "No")")
            Text("Visible: \(parameter.visible ? "Yes" : "No")")
            if let signalIndex = parameter.signalIndex {
                Text("Signal Index: \(signalIndex)")
            } else {
                Text("Signal Index: Not Available")
            }
            Text("IO Type: \(parameter.ioType)")
        }
    }
    struct ExternalDataRefView: View {
        let ref: ExternalDataRef

        var body: some View {
            DisclosureGroup(ref.id) {
                Text("ID: \(ref.id)")
                Text("File: \(ref.file)")
                Text("Tag: \(ref.tag)")
                Text("Type: \(ref.type)")
            }
        }
    }
    struct PortView: View {
        let port: Port

        var body: some View {
            Text("Tag: \(port.tag)")
            Text("Meta: \(port.meta)")
        }
    }
    struct InletOutletView: View {
        let inletOutlet: InletOutlet

        var body: some View {
            let indexString: String = if let index = inletOutlet.index {
                String(index)
            } else {
                ""
            }
            let tagString = if let tag = inletOutlet.tag {
                ": \(tag)"
            } else {
                ""
            }

            Text("\(inletOutlet.type.capitalizedSentence) \(indexString)\(tagString)")
        }
    }
    struct MetaView: View {
        let meta: Meta

        var body: some View {
            Text("architecture: \(meta.architecture)")
            Text("filename: \(meta.filename)")
            Text("rnboobjname: \(meta.rnboobjname)")
            Text("maxversion: \(meta.maxversion)")
            Text("rnboversion: \(meta.rnboversion)")
            Text("name: \(meta.name)")
        }
    }

//Bestand: RNBO/Interface/RNBODescription.swift
struct RNBODescription: Codable {
    let parameters: [ParameterInfo]
    let numParameters, numSignalInParameters, numSignalOutParameters: Int
    let numInputChannels, numOutputChannels, numMidiInputPorts, numMidiOutputPorts: Int
    let externalDataRefs: [ExternalDataRef]
    let patcherSerial: Int
    let inports, outports: [Port]
    let inlets, outlets: [InletOutlet]
    let presetid: String
    let meta: Meta
}
struct ParameterInfo: Codable {
    let type: String
    let index: Int
    let name, paramId: String
    let minimum, maximum, exponent: Double
    let steps: Int
    let initialValue: Double
    let isEnum: Bool
    let enumValues: [EnumValue]
    let displayName, unit: String
    let order: Int
    let debug, visible: Bool
    let signalIndex: Int?
    let ioType: String
}
struct ExternalDataRef: Codable {
    let id, file, type, tag: String
}
struct Port: Codable {
    let tag, meta: String
}
struct InletOutlet: Codable {
    let type: String
    let index: Int?
    let tag, meta: String?

    private enum CodingKeys: String, CodingKey {
        case type, index, tag, meta
    }
}
struct Meta: Codable {
    let architecture, filename, rnboobjname, maxversion: String
    let rnboversion, name: String
}
struct JSONNull: Codable, Hashable {}
struct EnumValue: Codable {
    let string: String

    init(from decoder: Decoder) throws {
        let container = try decoder.singleValueContainer()
        if let intVal = try? container.decode(Int.self) {
            string = String(intVal)
        } else if let doubleVal = try? container.decode(Double.self) {
            string = String(doubleVal)
        } else if let stringVal = try? container.decode(String.self) {
            string = stringVal
        } else if container.decodeNil() {
            string = "null"
        } else {
            throw DecodingError.typeMismatch(EnumValue.self, DecodingError.Context(codingPath: decoder.codingPath, debugDescription: "Failed to decode JSONAny"))
        }
    }

    func encode(to encoder: Encoder) throws {
        var container = encoder.singleValueContainer()
        try container.encode(string)
    }
}

//Bestand: RNBO/Interface/RNBOParameter.swift
struct RNBOParameter {
    var value: Double
    let info: ParameterInfo

    var valueNormalized: Double {
        get {
            value.toNormalised(minValue: info.minimum, maxValue: info.maximum, factor: info.exponent)
        }
        set {
            value = newValue.fromNormalised(minValue: info.minimum, maxValue: info.maximum, factor: info.exponent)
        }
    }

    init(_ info: ParameterInfo) {
        value = info.initialValue.clip(from: info.minimum, to: info.maximum)
        self.info = info
    }
}

//Bestand: RNBO/Interface/RNBOAudioUnitHostModel.swift
class RNBOAudioUnitHostModel: ObservableObject {
    private let audioEngine = RNBOAudioEngine()
    private let audioUnit: RNBOAudioUnit
    private let eventHandler = RNBOEventHandler()
    @Published var parameters: [RNBOParameter]
    @Published var showDescription: Bool = false
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

        audioUnit = audioEngine.getAudioUnit()
        parameters = description?.getParametersArray() ?? []
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
        audioUnit.sendNoteOnMessage(withPitch: pitch, velocity: velocity, channel: channel)
    }

    func sendNoteOff(_ pitch: UInt8, releaseVelocity: UInt8 = 0, channel: UInt8 = 0) {
        audioUnit.sendNoteOffMessage(withPitch: pitch, releaseVelocity: releaseVelocity, channel: channel)
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

//Bestand: RNBO/Interface/RNBOEventHandler.swift
class RNBOEventHandler: NSObject, RNBOEventHandlerProtocol {
    var rnbo: RNBOContext?

    func handle(_ event: RNBOParameterEvent) {
        if let rnbo = rnbo {
            DispatchQueue.main.async {
                rnbo.parameters[event.index].value = event.value
            }

            let p = rnbo.parameters[event.index]
            print("\(p.info.displayName): \(p.value)")
        }
    }

    func handle(_ event: RNBOMidiEvent) {
        let data = [event.midiData.0, event.midiData.1, event.midiData.2].prefix(event.length)
        print("Received MIDI: \(data)")

        let statusByte = event.midiData.0
        let channel = statusByte & 0x0F
        guard let command = MidiCommand(statusByte: statusByte) else {
            print("Unknown MIDI Command")
            return
        }

        switch command {
        case .noteOff:
            let note = event.midiData.1
            let velocity = event.midiData.2
            print("Note Off: Note \(note), Velocity \(velocity), Channel \(channel + 1)")

        case .noteOn:
            let note = event.midiData.1
            let velocity = event.midiData.2
            print("Note On: Note \(note), Velocity \(velocity), Channel \(channel + 1)")

        case .polyphonicKeyPressure:
            let note = event.midiData.1
            let pressure = event.midiData.2
            print("Polyphonic Key Pressure: Note \(note), Pressure \(pressure), Channel \(channel + 1)")

        case .controlChange:
            let controller = event.midiData.1
            let value = event.midiData.2
            print("Control Change: Controller \(controller), Value \(value), Channel \(channel + 1)")

        case .programChange:
            let program = event.midiData.1
            print("Program Change: Program \(program), Channel \(channel + 1)")

        case .channelPressure:
            let pressure = event.midiData.1
            print("Channel Pressure: Pressure \(pressure), Channel \(channel + 1)")

        case .pitchBend:
            let lsb = event.midiData.1
            let msb = event.midiData.2
            let value = (Int(msb) << 7) + Int(lsb)
            print("Pitch Bend: Value \(value), Channel \(channel + 1)")
        }
    }

    func handle(_ event: RNBOMessageEvent) {
//        print("Message from outport: \(event.tag): \(event.numValue)")
        // TODO:
    }

    func handle(_ event: RNBOPresetEvent) {
        // TODO:
    }

    func handle(_ event: RNBOTempoEvent) {
        // TODO:
    }

    func handle(_ event: RNBOTransportEvent) {
        // TODO:
    }

    func handle(_ event: RNBOBeatTimeEvent) {
        // TODO:
    }

    func handle(_ event: RNBOTimeSignatureEvent) {
        // TODO:
    }

    func handle(_ event: RNBOStartupEvent) {
        // TODO:
    }
}

//Bestand: RNBO/Interface/RNBOAudioEngine.swift
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
