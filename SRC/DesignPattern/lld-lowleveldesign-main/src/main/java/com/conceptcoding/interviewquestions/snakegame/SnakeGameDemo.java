package com.conceptcoding.interviewquestions.snakegame;

import javax.swing.AbstractAction;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.InputMap;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.KeyStroke;
import javax.swing.SwingUtilities;
import javax.swing.Timer;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;

public class SnakeGameDemo {

    private static final int TICK_MS = 140;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(SnakeGameDemo::launch);
    }

    private static void launch() {
        SnakeGame game = new SnakeGame(18, 18);
        SnakeGamePanel gamePanel = new SnakeGamePanel(game);
        JLabel scoreLabel = new JLabel();
        JLabel helpLabel = new JLabel("Arrows/WASD to move, Space to pause, R to restart");
        helpLabel.setFont(helpLabel.getFont().deriveFont(Font.PLAIN, 12f));

        Timer timer = new Timer(TICK_MS, event -> {
            game.tick();
            syncLabels(game, scoreLabel);
            gamePanel.repaint();
        });
        timer.start();

        JFrame frame = new JFrame("Snake");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new BorderLayout(12, 12));
        frame.getRootPane().setBorder(BorderFactory.createEmptyBorder(12, 12, 12, 12));

        JPanel header = new JPanel(new FlowLayout(FlowLayout.LEFT, 12, 0));
        header.add(scoreLabel);
        header.add(helpLabel);

        JPanel controls = new JPanel();
        controls.setLayout(new BoxLayout(controls, BoxLayout.Y_AXIS));
        controls.add(buildCenteredRow(button("Up", actionEvent -> game.changeDirection(Direction.UP))));
        controls.add(buildCenteredRow(
                button("Left", actionEvent -> game.changeDirection(Direction.LEFT)),
                button("Pause", actionEvent -> game.togglePause()),
                button("Right", actionEvent -> game.changeDirection(Direction.RIGHT))
        ));
        controls.add(buildCenteredRow(
                button("Down", actionEvent -> game.changeDirection(Direction.DOWN)),
                button("Restart", actionEvent -> game.reset())
        ));

        bindKey(gamePanel, "UP", () -> game.changeDirection(Direction.UP));
        bindKey(gamePanel, "W", () -> game.changeDirection(Direction.UP));
        bindKey(gamePanel, "DOWN", () -> game.changeDirection(Direction.DOWN));
        bindKey(gamePanel, "S", () -> game.changeDirection(Direction.DOWN));
        bindKey(gamePanel, "LEFT", () -> game.changeDirection(Direction.LEFT));
        bindKey(gamePanel, "A", () -> game.changeDirection(Direction.LEFT));
        bindKey(gamePanel, "RIGHT", () -> game.changeDirection(Direction.RIGHT));
        bindKey(gamePanel, "D", () -> game.changeDirection(Direction.RIGHT));
        bindKey(gamePanel, "SPACE", game::togglePause);
        bindKey(gamePanel, "R", game::reset);

        syncLabels(game, scoreLabel);

        frame.add(header, BorderLayout.NORTH);
        frame.add(gamePanel, BorderLayout.CENTER);
        frame.add(controls, BorderLayout.SOUTH);
        frame.pack();
        frame.setMinimumSize(new Dimension(480, 620));
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        gamePanel.requestFocusInWindow();
    }

    private static void syncLabels(SnakeGame game, JLabel scoreLabel) {
        String statusText = switch (game.getStatus()) {
            case READY -> "Ready";
            case RUNNING -> "Running";
            case PAUSED -> "Paused";
            case GAME_OVER -> "Game Over";
        };
        scoreLabel.setText("Score: " + game.getScore() + " | " + statusText);
    }

    private static JPanel buildCenteredRow(JComponent... components) {
        JPanel row = new JPanel(new FlowLayout(FlowLayout.CENTER, 8, 4));
        for (JComponent component : components) {
            row.add(component);
        }
        return row;
    }

    private static JButton button(String text, java.awt.event.ActionListener listener) {
        JButton button = new JButton(text);
        button.addActionListener(listener);
        return button;
    }

    private static void bindKey(JComponent component, String key, Runnable action) {
        InputMap inputMap = component.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW);
        inputMap.put(KeyStroke.getKeyStroke(key), key);
        component.getActionMap().put(key, new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent event) {
                action.run();
            }
        });
    }
}
