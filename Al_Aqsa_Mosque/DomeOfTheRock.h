#pragma once

class DomeOfTheRock
{


public:

	DomeOfTheRock();

	void arch(db sectorCount, db radius, db thickness = 0);

	void drawInnerRoof();

	void drawLeadRoof();

	void drawRing(db innerR, db outerR, db height, int sectorCnt, int texture1, int texture2, bool isHalf);

	void drawPipe(db innerR, db outerR, db height, int sectorCnt, int textures[], bool isHalf, bool isArch);

	void drawColumn(db pillarRadius, db pillarHeight, int texture, int sectorCnt = 12, bool bracelets = true);

	void drawEntrancePillar(db pillarRadius, db pillarHeight, db basesWidth, int texture);

	void drawArcadePillar(db pillarRadius, db pillarHeight, db basesWidth, int texture);

	void drawDrumPillar(db pillarRadius, db pillarHeight, db basesWidth, int texture);

	void drawEntrance(db doorWidth, db doorHeight);

	void drawArch(db innerR, db outerR, db height, int sectorCnt, int textures[]);

	void drawWalls(db openTheDoor);

	void drawArcadeSide();

	void drawArcade();

	void drawDrum();

	void drawFence(db heightOfWall);

	void drawDomes();

	void drawOctagon(const Constraints& c, int textures[]);

	void draw(db openTheDoor);

	void draw();


	//dome of souls 

	void drawDomeOfSoulsPillar(db pillarHeight, db pillarRadius, db basesWidth, int texture);

	void drawDomeOfSouls();

	//dome of the prophet

	void drawDomeOfThePorphetPillar(db pillarHeight, db pillarRadius, db basesWidth, int texture);

	void drawDomeOfTheProphet();


	void drawDomeOfAscentionPillar(db pillarHeight, db pillarRadius, db basesWidth, int texture);

	void drawDomeOfAscention();

	void drawDomeOfKhalili();

private:

	int
		ROOF1, ROOF2, ROOF3,
		BRIDGE1, BRIDGE2,
		ROCK,
		FENCE, MARBLE_FENCE,
		FOOT1, FOOT2, FOOT3, FOOT4, FOOT5,
		ARCH1, ARCH2, ARCH3, ARCH4, ARCH5, ARCH6, ARCH7, ARCH8, LEAD, ARCH10,
		DRUM1, DRUM2, DRUM3, DRUM4, DRUM5,
		DOME1, DOME3, DOME2,
		PILLAR1, PILLAR2,
		MARBLE1, MARBLE2, MARBLE3, MARBLE4, MARBLE5, MARBLE6, MARBLE7, MARBLE8,
		LIME_STONE1, LIME_STONE2, LIME_STONE3,WHITE_STONE, WOOD,
		TIER1, TIER2, TIER3, TIER4,
		WALL1, WALL2, WALL3, WALL4, WALL5, WALL6,
		DOOR1, DOOR2, DOOR3,
		CARPET,KHALILI1, KHALILI2, KHALILI3, KHALILI4;

	MosqueDrawer mosqueDrawer;

	int domeOfTheRockDisplayList;

};

