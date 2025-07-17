//
//  MIDISequencer.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Frans-Jan Wind on 17/07/2025.
//

import AudioKit
import Foundation

/// Een sequencer die MIDI-events laadt of genereert,
/// en deze via DispatchQueue op tijd stuurt naar de RNBOAudioUnitHostModel.
class MIDISequencer: ObservableObject {
    private let sequencer = AppleSequencer()
    private var noteEvents: [MIDINoteData] = []
    private var sequenceLength: TimeInterval = 0
    private var isPlaying = false
    private var scheduledItems: [DispatchWorkItem] = []
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

    /// Genereer een random “vier‐beat” sequence met 8ste/16de noten en wat rusten.
    func generateRandomSequence() {
        clearAllTracks()
        guard let track = sequencer.newTrack() else {
            print("❌ Kan geen nieuwe track maken.")
            return
        }
        track.clear()
        // Bouw 4 beats op
        let totalBeats = 4.0
        var posBeats = 0.0
        while posBeats < totalBeats {
            let isRest = Bool.random() && Bool.random()   // ca. 25% rust
            let dur = Bool.random() ? 0.25 : 0.5          // 16e of 8e
            if !isRest {
                let note = MIDINoteNumber(Int.random(in: 60...72))
                let vel  = MIDIVelocity(Int.random(in: 60...100))
                track.add(noteNumber: note,
                          velocity: vel,
                          position: Duration(beats: posBeats),
                          duration: Duration(beats: dur))
            }
            posBeats += dur
        }
        // Haal de gegenereerde events op
        noteEvents = track.getMIDINoteData()
        sequenceLength = totalBeats * (60.0 / sequencer.tempo)

        print("🎲 Willekeurige sequence: \(noteEvents.count) events")
    }

    /// Start de playback-loop
    func play() {
        guard !isPlaying, noteEvents.count > 0 else {
            if noteEvents.isEmpty { print("⚠️ Laad eerst een sequence of genereer er een.") }
            return
        }
        isPlaying = true
        scheduleLoop(offset: 0)
        print("▶︎ Sequencer gestart")
    }

    /// Stop playback en breek geplande DispatchWorkItems af
    func stop() {
        guard isPlaying else { return }
        isPlaying = false
        for item in scheduledItems {
            item.cancel()
        }
        scheduledItems.removeAll()
        print("■ Sequencer gestopt")
    }

    /// Recursief: plan alle note-on/off events voor één iteratie en plan de volgende loop
    private func scheduleLoop(offset: TimeInterval) {
        guard isPlaying else { return }
        for event in noteEvents {
            // note-on
            let onTime  = offset + event.position.seconds
            let onItem  = DispatchWorkItem { [weak self] in
                self?.rnbo?.sendNoteOn(event.noteNumber, velocity: event.velocity)
            }
            DispatchQueue.main.asyncAfter(deadline: .now() + onTime, execute: onItem)
            scheduledItems.append(onItem)

            // note-off
            let offTime = offset + event.position.seconds + event.duration.seconds
            let offItem = DispatchWorkItem { [weak self] in
                self?.rnbo?.sendNoteOff(event.noteNumber)
            }
            DispatchQueue.main.asyncAfter(deadline: .now() + offTime, execute: offItem)
            scheduledItems.append(offItem)
        }
        // plan volgende loop‐iteratie
        let loopItem = DispatchWorkItem { [weak self] in
            self?.scheduleLoop(offset: offset + self!.sequenceLength)
        }
        DispatchQueue.main.asyncAfter(deadline: .now() + offset + sequenceLength, execute: loopItem)
        scheduledItems.append(loopItem)
    }
}
