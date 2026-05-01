package com.conceptcoding.interviewquestions.snakegame;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class SnakeGame {

    private final int rows;
    private final int columns;
    private final FoodSpawner foodSpawner;
    private final int initialLength;

    private Deque<Position> snake;
    private Direction currentDirection;
    private Direction pendingDirection;
    private Position food;
    private GameStatus status;
    private int score;
    private int foodSeed;

    public SnakeGame(int rows, int columns) {
        this(rows, columns, 3, new SequentialFoodSpawner());
    }

    public SnakeGame(int rows, int columns, int initialLength, FoodSpawner foodSpawner) {
        if (rows < 5 || columns < 5) {
            throw new IllegalArgumentException("Board must be at least 5x5.");
        }
        if (initialLength < 2 || initialLength >= columns) {
            throw new IllegalArgumentException("Initial length must fit the board.");
        }
        this.rows = rows;
        this.columns = columns;
        this.initialLength = initialLength;
        this.foodSpawner = foodSpawner;
        reset();
    }

    public void reset() {
        snake = new ArrayDeque<>();
        int centerRow = rows / 2;
        int headColumn = Math.max(initialLength - 1, columns / 3);

        for (int index = 0; index < initialLength; index++) {
            snake.addLast(new Position(centerRow, headColumn - index));
        }

        currentDirection = Direction.RIGHT;
        pendingDirection = currentDirection;
        score = 0;
        status = GameStatus.READY;
        foodSeed = headColumn + 2;
        food = placeFood();
    }

    public void tick() {
        if (status == GameStatus.GAME_OVER || status == GameStatus.PAUSED) {
            return;
        }

        status = GameStatus.RUNNING;
        if (!pendingDirection.isOpposite(currentDirection)) {
            currentDirection = pendingDirection;
        }

        Position nextHead = snake.peekFirst().move(currentDirection);
        boolean isEating = nextHead.equals(food);

        Set<Position> occupied = new HashSet<>(snake);
        if (!isEating) {
            occupied.remove(snake.peekLast());
        }

        if (isOutsideBoard(nextHead) || occupied.contains(nextHead)) {
            status = GameStatus.GAME_OVER;
            return;
        }

        snake.addFirst(nextHead);
        if (isEating) {
            score++;
            foodSeed += 7;
            food = placeFood();
            if (food == null) {
                status = GameStatus.GAME_OVER;
            }
        } else {
            snake.removeLast();
        }
    }

    public void changeDirection(Direction direction) {
        if (direction == null) {
            return;
        }
        if (snake.size() > 1 && direction.isOpposite(currentDirection)) {
            return;
        }
        pendingDirection = direction;
    }

    public void togglePause() {
        if (status == GameStatus.GAME_OVER) {
            return;
        }
        status = (status == GameStatus.PAUSED) ? GameStatus.RUNNING : GameStatus.PAUSED;
    }

    public List<Position> getSnake() {
        return List.copyOf(snake);
    }

    public Position getFood() {
        return food;
    }

    public Position getHead() {
        return snake.peekFirst();
    }

    public int getRows() {
        return rows;
    }

    public int getColumns() {
        return columns;
    }

    public int getScore() {
        return score;
    }

    public GameStatus getStatus() {
        return status;
    }

    public Direction getCurrentDirection() {
        return currentDirection;
    }

    private boolean isOutsideBoard(Position position) {
        return position.row() < 0 || position.row() >= rows || position.column() < 0 || position.column() >= columns;
    }

    private Position placeFood() {
        return foodSpawner.spawn(rows, columns, snake, foodSeed);
    }
}
