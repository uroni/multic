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

package src.overlay.qlearn;

import oversim.common.BaseOverlay;

simple QLearnCC extends BaseOverlay
{
	parameters: 
		@class(QLearnCC);
		int maxPeers;
		int maxRate;
		int numHops;
		int largestKey;
		int incoming_rate;
		int packetsize;
		double alpha;
		double lambda;
		double reinf_up;
		double reinf_down;
		double reinf_down_cong;
		double epsilon;
		double rttalpha;
		double rttgamma;
		
		int incoming_rate2;
		int rate_switch_border;
		double rate_switch_time;
}