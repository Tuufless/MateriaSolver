#include <iostream>
#include "CrafterStats.h"
#include <algorithm>
#include <vector>
#include <array>

std::vector<std::array<int, 6>> Solve(const Stats& base, const Stats& target, int numGuaranteedSlots, int numOvermeldSlots) {
	// six parameters:
	// #craftVI, #craftV, #controlVI, #controlV, #cpVI, #cpV

	// however, this isn't realy six-dimensional, as there are four dependancies
	// craftVI + controlVI + cpVI = numGuaranteedSlots
	// craftV + controlV + cpV = numOvermeldSlots
	// craftV = ceil(((targetcraft - basecraft) - (16 * craftVI)) / 11);
	// cpVI = numGuaranteedSlots - craftVI - controlVI
	
	static const Stats craftVI(16, 0, 0);
	static const Stats craftV(11, 0, 0);
	static const Stats controlVI(0, 10, 0);
	static const Stats controlV(0, 7, 0);
	static const Stats cpVI(0, 0, 8);
	static const Stats cpV(0, 0, 6);

	const Stats diff = target - base;

	auto round_up = [&](float x) {
		return static_cast<int>(std::ceil(x));
	};

	std::vector<std::array<int, 6>> result;

	for (int numCraftVI = 0; numCraftVI <= numGuaranteedSlots; ++numCraftVI) {
		for (int numControlVI = 0; numControlVI <= numGuaranteedSlots - numCraftVI; ++numControlVI) {
			int numCPVI = numGuaranteedSlots - numCraftVI - numControlVI;
			
			int numCraftV = round_up(static_cast<float>(diff.craftsmanship - 16 * numCraftVI) / 11.0f);
			int numControlV = round_up(static_cast<float>(diff.control - 10 * numControlVI) / 7.0f);
			int numCPV = round_up(static_cast<float>(diff.cp - 8 * numCPVI) / 6.0f);

			if (numCraftV + numControlV + numCPV <= numOvermeldSlots && numCPVI >= 0 && numCraftV >= 0 && numControlV >= 0 && numCPV >= 0) {
				std::array<int, 6> melds;
				melds[0] = numCraftVI;
				melds[1] = numControlVI;
				melds[2] = numCPVI;
				melds[3] = numCraftV;
				melds[4] = numControlV;
				melds[5] = numCPV;

				result.push_back(melds);
			}
		}
	}

	return result;
}

int main()
{
	Stats base(1590, 1470, 395);
	Stats target(1790, 1680, 487);

	std::vector<std::array<int, 6>> melds = Solve(base, target, 16, 42);

	return 0;
}