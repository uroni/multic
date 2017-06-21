//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 
package src.overlay.aimd;

import oversim.common.IOverlay;

module AimdCCMod like IOverlay
{
    gates:
        input udpIn;   // gate from the UDP layer
        output udpOut;    // gate to the UDP layer
        input appIn;   // gate from the application
        output appOut;    // gate to the application

    submodules:
        aimdcc: AimdCC;

    connections allowunconnected:
        udpIn --> aimdcc.udpIn;
        udpOut <-- aimdcc.udpOut;
        appIn --> aimdcc.appIn;
        appOut <-- aimdcc.appOut;
}