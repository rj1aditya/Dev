package com.conceptcoding.interviewquestions.snakegame;

import javax.swing.JPanel;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;

public class SnakeGamePanel extends JPanel {

    private static final int CELL_SIZE = 24;
    private static final Color BACKGROUND = new Color(247, 247, 247);
    private static final Color GRID = new Color(222, 222, 222);
    private static final Color SNAKE = new Color(46, 125, 50);
    private static final Color HEAD = new Color(27, 94, 32);
    private static final Color FOOD = new Color(198, 40, 40);

    private final SnakeGame game;

    public SnakeGamePanel(SnakeGame game) {
        this.game = game;
        setBackground(BACKGROUND);
        setPreferredSize(new Dimension(game.getColumns() * CELL_SIZE, game.getRows() * CELL_SIZE));
        setFocusable(true);
    }

    @Override
    protected void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);

        Graphics2D g2d = (Graphics2D) graphics.create();
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        for (int row = 0; row < game.getRows(); row++) {
            for (int column = 0; column < game.getColumns(); column++) {
                int x = column * CELL_SIZE;
                int y = row * CELL_SIZE;
                g2d.setColor(BACKGROUND);
                g2d.fillRect(x, y, CELL_SIZE, CELL_SIZE);
                g2d.setColor(GRID);
                g2d.drawRect(x, y, CELL_SIZE, CELL_SIZE);
            }
        }

        Position food = game.getFood();
        if (food != null) {
            drawCell(g2d, food, FOOD, 4);
        }

        for (int index = game.getSnake().size() - 1; index >= 0; index--) {
            Position part = game.getSnake().get(index);
            drawCell(g2d, part, index == 0 ? HEAD : SNAKE, 2);
        }

        if (game.getStatus() == GameStatus.PAUSED || game.getStatus() == GameStatus.GAME_OVER) {
            String message = game.getStatus() == GameStatus.PAUSED ? "Paused" : "Game Over";
            g2d.setColor(new Color(255, 255, 255, 220));
            g2d.fillRoundRect(18, 18, getWidth() - 36, 56, 12, 12);
            g2d.setColor(Color.DARK_GRAY);
            g2d.setFont(getFont().deriveFont(Font.BOLD, 22f));
            g2d.drawString(message, 32, 54);
        }

        g2d.dispose();
    }

    private void drawCell(Graphics2D g2d, Position position, Color color, int inset) {
        int x = position.column() * CELL_SIZE + inset;
        int y = position.row() * CELL_SIZE + inset;
        int size = CELL_SIZE - (inset * 2);
        g2d.setColor(color);
        g2d.fillRoundRect(x, y, size, size, 8, 8);
    }
}
