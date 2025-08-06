//
//  OctaafStepperView.swift
//  Sonik
//
//  Created by Frans-Jan Wind on 06/08/2025.
//


import SwiftUI

struct OctaafStepperView: View {
    @EnvironmentObject var rnbo: RNBOAudioUnitHostModel

    let minOctave = -6
    let maxOctave = 6

    var body: some View {
        VStack(spacing: 6) {
            HStack(spacing: 15) {
                Button {
                    if rnbo.currentOctave > minOctave {
                        rnbo.sendAllNotesOff()
                        rnbo.currentOctave -= 1
                    }
                } label: {
                    Image(systemName: "minus.circle")
                }
                .buttonStyle(.borderedProminent)
                .disabled(rnbo.currentOctave <= minOctave)

                Button {
                    if rnbo.currentOctave < maxOctave {
                        rnbo.sendAllNotesOff()
                        rnbo.currentOctave += 1
                    }
                } label: {
                    Image(systemName: "plus.circle")
                }
                .buttonStyle(.borderedProminent)
                .disabled(rnbo.currentOctave >= maxOctave)
            }

            Text("Octaaf: \(rnbo.currentOctave)")
                .font(.footnote)
                .foregroundColor(.secondary)
        }
    }
}
