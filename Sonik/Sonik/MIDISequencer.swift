//
//  MIDISequencer.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Frans-Jan Wind on 17/07/2025.
//

import AudioKit

/// Een sequencer die MIDI-events laadt of genereert,
/// en deze via DispatchQueue op tijd stuurt naar de RNBOAudioUnitHostModel.
class MIDISequencer: ObservableObject {
    private let sequencer = AppleSequencer()
    @Published private(set) var noteEvents: [MIDINoteData] = []
    private var sequenceLength: TimeInterval = 0
    private var isPlaying = false
    private var scheduled: [DispatchWorkItem] = []
    private weak var rnbo: RNBOAudioUnitHostModel?

    /// Initialiseer met je RNBO-host zodat we sendNoteOn/Off kunnen aanroepen.
    init(rnbo: RNBOAudioUnitHostModel) {
        self.rnbo = rnbo
    }

    /// Ruim alle tracks en geplande events op.
    func clearAllTracks() {
        // Verwijder alle bestaande tracks
        for index in sequencer.tracks.indices.reversed() {
            sequencer.tracks[index].clear()  // lege track
            sequencer.deleteTrack(trackIndex: index)
        }
        noteEvents.removeAll()
        sequenceLength = 0
        stop()
    }

    /// Laad een `.mid` uit de bundle (zonder extensie meegeven).
    func loadMIDIFile(named fileName: String) {
        clearAllTracks()
        guard let url = Bundle.main.url(forResource: fileName, withExtension: "mid") else {
            print("❌ MIDI \(fileName).mid niet gevonden in bundle.")
            return
        }
        
        sequencer.loadMIDIFile(fromURL: url)
        // We pakken de eerste track
        if let track = sequencer.tracks.first {
            noteEvents = track.getMIDINoteData()
            sequenceLength = sequencer.length.seconds
            print("✅ MIDI geladen: \(noteEvents.count) events, lengte \(sequenceLength)s")
        }
    }
    
    /// Laadt of genereert, en prepareert events
    func loadMIDI(named name: String) {
        reset()
        guard let url = Bundle.main.url(forResource: name, withExtension: "mid") else { return }
        sequencer.loadMIDIFile(fromURL: url)
        extractEvents()
    }
    
    // Nieuwe methode voor Arpeggio-generatie
    func generateArpeggioSequence(
        chordNotes: [MIDINoteNumber] = [60, 64, 67],
        pattern: [Int] = [0, 1, 2, 1],
        octaveRange: Int = 1,
        repeats: Int = 4,
        noteDuration: Duration = Duration(beats: 0.25),
        velocity: MIDIVelocity = 100
    ) {
        clearAllTracks()
        
        guard let track = sequencer.newTrack() else {
            print("❌ Kan geen nieuwe track maken.")
            return
        }
        
        // 16e noot grid definitie
        let gridResolution = 0.25
        var currentBeat = 0.0
        
        for _ in 0..<repeats {
            for octave in 0..<octaveRange {
                for index in pattern {
                    let midiNote = chordNotes[index % chordNotes.count] + MIDINoteNumber(octave * 12)
                    // Zorg dat elke noot exact op het 16e-grid geplaatst wordt
                    let quantizedBeat = (currentBeat / gridResolution).rounded() * gridResolution
                    track.add(noteNumber: midiNote,
                              velocity: velocity,
                              position: Duration(beats: quantizedBeat),
                              duration: noteDuration)
                    currentBeat += gridResolution
                }
            }
        }
        
        // Sequence-length precies op maat zetten
        sequencer.setLength(Duration(beats: currentBeat))
        
        noteEvents = track.getMIDINoteData()
        sequenceLength = currentBeat * (60.0 / sequencer.tempo)
        
        print("🎶 Strakke arpeggio sequence: \(noteEvents.count) events")
    }

    /// Start de playback-loop
    func play() {
        guard !isPlaying, noteEvents.count > 0 else {
            if noteEvents.isEmpty { print("⚠️ Laad eerst een sequence of genereer er een.") }
            return
        }
        isPlaying = true
        scheduleLoop(at: 0)
        print("▶︎ Sequencer gestart")
    }

    /// Stop playback en breek geplande DispatchWorkItems af
    func stop() {
        guard isPlaying else { return }
        isPlaying = false
        scheduled.forEach { $0.cancel() }; scheduled.removeAll()
                noteEvents.map(\.noteNumber).forEach { rnbo?.sendNoteOff($0) }
        print("■ Sequencer gestopt")
    }
        
    //–– Helpers ––
    private func reset() {
        sequencer.tracks.forEach { $0.clear() }
        sequencer.tracks.indices.reversed().forEach { sequencer.deleteTrack(trackIndex: $0) }
        noteEvents = []
        sequenceLength = 0
        stop()
    }

    private func extractEvents() {
        if let t = sequencer.tracks.first {
            noteEvents = t.getMIDINoteData()
            sequenceLength = sequencer.length.seconds
        }
    }
    
    /// Plant de Note-On en Note-Off DispatchWorkItems
    private func schedule(_ note: UInt8,
                          vel: UInt8,
                          at time: TimeInterval,
                          dur duration: TimeInterval) {
        // Note-On
        let onItem = DispatchWorkItem { [weak self] in
            self?.rnbo?.sendNoteOn(note, velocity: vel)
        }
        DispatchQueue.main.asyncAfter(deadline: .now() + time, execute: onItem)
        
        // Note-Off
        let offItem = DispatchWorkItem { [weak self] in
            self?.rnbo?.sendNoteOff(note)
        }
        DispatchQueue.main.asyncAfter(deadline: .now() + time + duration, execute: offItem)
        
        scheduled.append(contentsOf: [onItem, offItem])
    }

    private func scheduleLoop(at offset: TimeInterval) {
        guard isPlaying else { return }
        noteEvents.forEach { e in
            schedule(e.noteNumber, vel: e.velocity, at: offset + e.position.seconds, dur: e.duration.seconds)
        }
        let loop = DispatchWorkItem { [weak self] in
            self?.scheduleLoop(at: offset + self!.sequenceLength)
        }
        DispatchQueue.main.asyncAfter(deadline: .now() + offset + sequenceLength, execute: loop)
        scheduled.append(loop)
    }
}
