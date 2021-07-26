#pragma once
#include <vector>
#include <map>
#include <string>

struct TalentScaling {

	const std::map<int, float> Elemental1 = {
		{1, 1.0f},
		{2, 1.075f},
		{3, 1.15f},
		{4, 1.25f},
		{5, 1.325f},
		{6, 1.4f},
		{7, 1.5f},
		{8, 1.6f},
		{9, 1.7f},
		{10, 1.8f},
		{11, 1.9f},
		{12, 2.0f},
		{13, 2.125f}
	};

	const std::map<int, float> Elemental1Alternative = {
		{1, 1.0f},
		{2, 1.075f},
		{3, 1.15f},
		{4, 1.25f},
		{5, 1.325f},
		{6, 1.4f},
		{7, 1.5f},
		{8, 1.6f},
		{9, 1.7f},
		{10, 1.8f},
		{11, 1.9f},
		{12, 2.04f},
		{13, 2.176f}
	};

	const std::map<int, float> Elemental2 = {
		{1, 1.0f},
		{2, 1.06f},
		{3, 1.12f},
		{4, 1.198f},
		{5, 1.257f},
		{6, 1.317f},
		{7, 1.395f},
		{8, 1.473f},
		{9, 1.551f},
		{10, 1.629f},
		{11, 1.707f},
		{12, 1.784f},
		{13, 1.862f}
	};

	const std::map<int, float> Physical1 = {
		{1, 1.0f},
		{2, 1.081f},
		{3, 1.163f},
		{4, 1.279f},
		{5, 1.36f},
		{6, 1.453f},
		{7, 1.581f},
		{8, 1.709f},
		{9, 1.837f},
		{10, 1.977f},
		{11, 2.116f},
		{12, 2.256f},
		{13, 2.395f}
	};

	const std::map<int, float> Physical1Alternative = {
		{1, 1.0f},
		{2, 1.081f},
		{3, 1.163f},
		{4, 1.279f},
		{5, 1.36f},
		{6, 1.453f},
		{7, 1.581f},
		{8, 1.709f},
		{9, 1.837f},
		{10, 1.977f},
		{11, 2.137f},
		{12, 2.325f},
		{13, 2.513f}
	};

	const std::map<int, float> Physical2 = {
		{1, 1.0f},
		{2, 1.068f},
		{3, 1.136f},
		{4, 1.227f},
		{5, 1.295f},
		{6, 1.375f},
		{7, 1.477f},
		{8, 1.580f},
		{9, 1.682f},
		{10, 1.784f},
		{11, 1.886f},
		{12, 1.989},
		{13, 2.091}
	};

	const std::map<int, float> ZhongliBurst = {
		{1, 1.0f},
		{2, 1.108f},
		{3, 1.216f},
		{4, 1.351f},
		{5, 1.473f},
		{6, 1.595f},
		{7, 1.757f},
		{8, 1.919f},
		{9, 2.081f},
		{10, 2.243f},
		{11, 2.405f},
		{12, 2.568f},
		{13, 2.703f}
	};

public:
	static TalentScaling& Get();
	TalentScaling(const TalentScaling&) = delete;
	std::map<std::string, const std::map<int, float>&> scaling_map;
private:
	TalentScaling();
};