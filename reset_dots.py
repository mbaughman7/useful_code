import board
import adafruit_dotstar as dotstar

dots = dotstar.DotStar(board.D6, board.D5, 3, brightness=0.2)

n_dots = len(dots)

  for dot in range(n_dots):
      dots[dot] = (0, 0, 0)
