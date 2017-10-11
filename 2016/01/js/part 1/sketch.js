var inputText = 'L1,R3,R1,L5,L2,L5,R4,L2,R2,R2,L2,R1,L5,R3,L4,L1,L2,R3,R5,L2,R5,L1,R2,L5,R4,R2,R2,L1,L1,R1,L3,L1,R1,L3,R5,R3,R3,L4,R4,L2,L4,R1,R1,L193,R2,L1,R54,R1,L1,R71,L4,R3,R191,R3,R2,L4,R3,R2,L2,L4,L5,R4,R1,L2,L2,L3,L2,L1,R4,R1,R5,R3,L5,R3,R4,L2,R3,L1,L3,L3,L5,L1,L3,L3,L1,R3,L3,L2,R1,L3,L1,R5,R4,R3,R2,R3,L1,L2,R4,L3,R1,L1,L1,R5,R2,R4,R5,L1,L1,R1,L2,L4,R3,L1,L3,R5,R4,R3,R3,L2,R2,L1,R4,R2,L3,L4,L2,R2,R2,L4,R3,R5,L2,R2,R4,R5,L2,L3,L2,R5,L4,L2,R3,L5,R2,L1,R1,R3,R3,L5,L2,L2,R5';
var input = inputText.split(',');
var n = input.length, i = 0, x = 0, y = 0, heading = 0;
var done = false, moving = false;
var current;
var turn;
var length;
var moved;

function setup() {
  createCanvas(600,600);
  background(0,255,128);
  stroke(0);
  fill(0);
}

function draw() {
  if (!done) {
    if (!moving) {
      current = input[i];
      turn = current.charAt(0);
      length = current.substr(1);
      if (turn == 'R') {
        turn = 1;
      } else if (turn == 'L') {
        turn = -1;
      }
      heading = (heading + turn + 4) % 4;
      moved = 0;
      moving = true;
    }
    if (moving) {
      if (moved >= length) {
        moving = false;
        i++;
      }
      else {
        if (heading % 2) {
          x = x + (2 - heading);
        } else {
          y = y + (1 - heading);
        }
        moved++;
        ellipse(x*2+width/2+200,height/2-y*2+200,1,1);
      }
    }
    if (i==n) {
      done = true;
      console.log(abs(x) + abs(y));
    }
  }
}
