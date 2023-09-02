# The Goal of "Gaussian"
To replicate the following p5.js code ([runnable here](https://editor.p5js.org/))
```
function setup() {
  createCanvas(400, 400);
}

function draw() {
  noStroke();
  fill(0, 10);

  // Uniform distribution.
  let x = random(width);
  let y = 25;
  circle(x, y, 5);

  // Gaussian distribution with sd = 1.
  x = randomGaussian(width/2);
  y = 50;
  circle(x, y, 5);

  // Gaussian distribution with sd = 10.
  x = randomGaussian(width/2, 30);
  y = 75;
  circle(x, y, 5);
  describe('Three horizontal black lines are filled in randomly. The top line spans entire canvas. The middle line is very short. The bottom line spans two-thirds of the canvas.');
}
```

and generate the resultant image

![image](https://github.com/ChristopherDrum/nature_of_code_v2/assets/320377/fc4bebe2-79f6-4345-b09a-6ce6efe02f01)

## Success
Using the function developed in this mini-project, which was then brought into the general "processing.h" file for use in "gaussian_visualization" I was able to generate this image in Raylib

![image](https://github.com/ChristopherDrum/nature_of_code_v2/assets/320377/57ed2e8f-f081-4278-9cf7-8fbfbcc1c28e)

This shows proper distribution, AFAIK. Rendering differences can't be helped (Raylib looks a little overly sharp to my eyes) at this time. Perhaps there is some softer anti-aliasing rendering we can apply?
