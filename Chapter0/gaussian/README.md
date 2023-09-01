#The Goal of "Gaussian"
To replicate the following p5.js code
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
