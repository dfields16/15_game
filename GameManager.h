

struct GameManager{
	//CONSTANTS
	//Format for game patterns
	/*Complete*/	const int CPTRN[4][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,0}};
	/*Beginner*/	const int BPTRN[4][4] = {{1,2,3,4}, {5,6,12,7}, {9,10,0,15}, {13,14,8,11}};
	/*Intermediate*/const int IPTRN[4][4] = {{1,6,3,4}, {5,0,2,11}, {9,10,14,7}, {13,15,12,8}};
	/*Advanced*/	const int APTRN[4][4] = {{6,5,11,4}, {10,13,2,1}, {9,15,7,3}, {14,12,8,0}};
	/*Expert*/		const int EPTRN[4][4] = {{0,12,11,13}, {15,14,10,9}, {3,7,6,2}, {4,8,5,1}};
	

	
};