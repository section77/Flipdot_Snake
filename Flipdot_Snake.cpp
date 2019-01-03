struct POINT {
    uint8_t x;
    uint8_t y;  
};

const uint8_t DIRECTION_UP = 0;
const uint8_t DIRECTION_DOWN = 1;
const uint8_t DIRECTION_LEFT = 2;
const uint8_t DIRECTION_RIGHT = 3;

bool gameIsRunning = false;
uint8_t direction = DIRECTION_RIGHT; // TODO enum?
POINT food;
vector<POINT> snake; // TODO use right data structure, needed: iterations, first, last, addFirst, removeLast

// TODO get from Flipdot_Control (extend interface)
Flipdot_Control control;
uint8_t displayWidth;
uint8_t displayHeight;

int score = 0;

Flipdot_Snake::Flipdot_Snake(Flipdot_Control control, uint8_t displayWidth, uint8_t displayHeight) {
	this->control = control;
	this->displayWidth = displayWidth;
	this->displayHeight = displayHeight;
}

void Flipdot_Snake::initializeSnake() {
	snake = new std::vector<POINT>;

	uint8_t middleY = displayHeight / 2;

	// initial size of 3, start with x-offset 2
	for (int x = 2; x < 5; x++) {
		snake.add(new POINT(x, middleY));
	}
}

void Flipdot_Snake::positionFood() {
	do {
		food.x = rand(0, displayWidth);
		food.y = rand(0, displayHeight);
	} while (!isFoodPositionValid());
}

void Flipdot_Snake::isFoodPositionValid() {
	for (int i = 0; i < sizeof(snake); i++) {
		if (snake[i].x == food.x && snake[i].y == food.y) {
			return false;
		}
	}
	return true;
}

void Flipdot_Snake::tick() {
	if (!gameIsRunning) {
		if (isStartRequested()) {
			startGame();
			gameIsRunning = true;
		}

		return;
	}

	modifyDirectionFromInputs();

	if (snakeWillHitBorder() || snakeWillHitSelf()) {
		endGame();
		gameIsRunning = false;
		return;
	}

	if (snakeWillEat()) {
		letSnakeEat();
		return;
	}

	letSnakeWalk();
}

void Flipdot_Snake::isStartRequested() {
	return true; // TODO check all button states if any is pressed
}

void Flipdot_Snake::modifyDirectionFromInputs() {
	if (false) { // TODO check up button state
		direction = DIRECTION_UP;
	} else if (false) { // TODO check down button state
		direction = DIRECTION_DOWN;
	} else if (false) { // TODO check left button state
		direction = DIRECTION_LEFT;
	} else if (false) { // TODO check right button state
		direction = DIRECTION_RIGHT;
	}
}

void Flipdot_Snake::printFood() {
	control.flipToColor(food.x, food.y);
}

void Flipdot_Snake::printSnake() {
	foreach (snake as point) { // TODO impl
		control.flipToColor(point.x, point.y);
	}
}

void Flipdot_Snake::letSnakeEat() {
	// TODO append current food position to snake front
	score++;
	positionFood();
	printFood();
}

void Flipdot_Snake::letSnakeWalk() {
	POINT nextPoint = getNextSnakePoint(); // TODO get next snake point
	// TODO append to front and flip to color
	// TODO flip last point to black
	// TODO remove last point
}

bool Flipdot_Snake::snakeWillHitBorder() {
	POINT nextPoint = getNextSnakePoint(); // TODO get next snake point
	return nextPoint.x < 0 
		|| nextPoint.x >= displayWidth 
		|| nextPoint.y < 0 
		|| nextPoint.y >= displayHeight;
}

bool Flipdot_Snake::snakeWillHitSelf() {
	POINT nextPoint = getNextSnakePoint(); // TODO get next snake point
	foreach (snake as point) { // TODO impl
		if (nextPoint.x == point.x && nextPoint.y == point.y) {
			return true;
		}
	}
	return false;
}

bool Flipdot_Snake::snakeWillEat() {
	POINT nextPoint = getNextSnakePoint(); // TODO get next snake point
	return nextPoint.x == food.x && nextPoint.y == food.y;
}

void Flipdot_Snake::startGame() {
	clearDisplay();

	initializeSnake();
	positionFood();

	printFood();
	printSnake();
}

void Flipdot_Snake::clearDisplay() {
	for (int x = 0; x < displayWidth; x++) {
		for (int y = 0; y < displayHeight; y++) {
			control.flipToBlack(x, y);
		}
	}
}

void Flipdot_Snake::endGame() {
	// TODO pint game over screen with score
}