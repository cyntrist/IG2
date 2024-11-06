#pragma once

class Game
{
	int stage;
	int lives;
	int points;
public:
	Game();
	~Game() = default;
	int getStage() const { return stage;}
	int getLives() const { return lives;}
	int getPoints() const { return points;}
	void addPoints(int pts) { points += pts; }
	void addLives(int lvs) { lives += lvs; }
	void changeStage(int stg) { stage = stg; }
};

