package com.conceptcoding.interviewquestions.snakegame;

import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

public class SequentialFoodSpawner implements FoodSpawner {

    @Override
    public Position spawn(int rows, int columns, Collection<Position> occupiedCells, int startIndex) {
        int totalCells = rows * columns;
        Set<Position> occupied = new HashSet<>(occupiedCells);

        for (int offset = 0; offset < totalCells; offset++) {
            int candidateIndex = Math.floorMod(startIndex + offset, totalCells);
            Position candidate = new Position(candidateIndex / columns, candidateIndex % columns);
            if (!occupied.contains(candidate)) {
                return candidate;
            }
        }

        return null;
    }
}
