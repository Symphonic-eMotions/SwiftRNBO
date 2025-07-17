//
//  ContentView.swift
//  SwiftRNBO_Example_multiplatfrom_SwiftUI
//
//  Created by Эльдар Садыков on 19.02.2023.
//

import SwiftUI

struct ContentView: View {
    @EnvironmentObject var rnbo: RNBOAudioUnitHostModel
    @EnvironmentObject var sequencer: MIDISequencer

    var body: some View {
        VStack(spacing: 10) {
            Buttons()

            #if !os(tvOS)
                if rnbo.showDescription {
                    DescriptionView()
                } else {
                    Sliders()
                    AudioKitKeyboard()
                    
                    HStack(spacing: 10) {
                        Button("Laad MIDI") {
                            sequencer.loadMIDIFile(named: "midiMelody")
                        }
                        Button("Genereer Willekeurig") {
                            sequencer.generateRandomSequence()
                        }
                        Button("Leegmaken") {
                            sequencer.clearAllTracks()
                        }
                    }
                    
                    HStack(spacing: 10) {
                        Button("▶︎ Play") { sequencer.play() }
                        Button("■ Stop") { sequencer.stop() }
                    }
                }
            #endif
        }
        .padding()
    }
}
