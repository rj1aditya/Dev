package com.conceptcoding.interviewquestions.snakegame;

import java.util.Collection;

public interface FoodSpawner {

    Position spawn(int rows, int columns, Collection<Position> occupiedCells, int startIndex);
}
