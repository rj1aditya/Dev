package com.conceptcoding.interviewquestions.snakegame;

import org.junit.jupiter.api.Test;

import java.util.ArrayDeque;
import java.util.Deque;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

class SnakeGameTest {

    @Test
    void tickMovesSnakeForwardByOneCell() {
        SnakeGame game = new SnakeGame(8, 8, 3, new SequentialFoodSpawner());
        Position originalHead = game.getHead();

        game.tick();

        assertEquals(originalHead.move(Direction.RIGHT), game.getHead());
        assertEquals(3, game.getSnake().size());
        assertEquals(GameStatus.RUNNING, game.getStatus());
    }

    @Test
    void eatingFoodGrowsSnakeAndIncreasesScore() {
        SnakeGame game = new SnakeGame(8, 8, 3, aheadFoodSpawner());

        game.tick();

        assertEquals(4, game.getSnake().size());
        assertEquals(1, game.getScore());
        assertEquals(new Position(game.getRows() / 2, game.getHead().column() + 1), game.getFood());
    }

    @Test
    void snakeCollidesWithWallAndEndsGame() {
        SnakeGame game = new SnakeGame(5, 5, 3, new SequentialFoodSpawner());

        for (int index = 0; index < 3; index++) {
            game.tick();
        }

        assertEquals(GameStatus.GAME_OVER, game.getStatus());
    }

    @Test
    void oppositeDirectionInputIsIgnored() {
        SnakeGame game = new SnakeGame(8, 8, 3, new SequentialFoodSpawner());

        game.changeDirection(Direction.LEFT);
        game.tick();

        assertEquals(Direction.RIGHT, game.getCurrentDirection());
        assertFalse(game.getHead().equals(new Position(game.getRows() / 2, 1)));
    }

    @Test
    void foodSpawnerSkipsOccupiedCells() {
        SequentialFoodSpawner spawner = new SequentialFoodSpawner();
        Deque<Position> occupied = new ArrayDeque<>();
        occupied.add(new Position(0, 0));
        occupied.add(new Position(0, 1));
        occupied.add(new Position(0, 2));

        Position food = spawner.spawn(2, 3, occupied, 0);

        assertEquals(new Position(1, 0), food);
    }

    @Test
    void resetRestoresInitialState() {
        SnakeGame game = new SnakeGame(8, 8, 3, aheadFoodSpawner());

        game.tick();
        game.togglePause();
        game.reset();

        assertEquals(0, game.getScore());
        assertEquals(3, game.getSnake().size());
        assertEquals(GameStatus.READY, game.getStatus());
        assertEquals(Direction.RIGHT, game.getCurrentDirection());
        assertTrue(game.getFood() != null);
    }

    private FoodSpawner aheadFoodSpawner() {
        return (rows, columns, occupiedCells, startIndex) -> {
            Position head = occupiedCells.iterator().next();
            Position candidate = new Position(head.row(), head.column() + 1);
            if (candidate.column() < columns && !occupiedCells.contains(candidate)) {
                return candidate;
            }
            return new Position(head.row() + 1, head.column());
        };
    }
}
