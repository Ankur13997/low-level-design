#include "ElevatorCar.h"

static inline int counterId = 0;

ElevatorCar::ElevatorCar(shared_ptr<InnerButtonDispatcher> innerButtonDispatcher) : id(++counterId) {
    status = ElevatorStatus::IDLE;
    display = make_shared<Display>();
    direction = Direction::UP;
    currentFloor = 0;
    innerButton = make_shared<InnerButton>( innerButtonDispatcher);
}

ElevatorCar::~ElevatorCar() {}

int ElevatorCar::getElevatorId() { return id; }

int ElevatorCar::getCurrentFloor() { return currentFloor; }

Direction ElevatorCar::getDirection() { return direction; }

ElevatorStatus ElevatorCar::getStatus() { return status; }

shared_ptr<Display> ElevatorCar::getDisplay() { return display; }

shared_ptr<InnerButton> ElevatorCar::getInnerButton() { return innerButton; }

void ElevatorCar::setCurrentFloor(int floor) { currentFloor = floor; }

void ElevatorCar::setDirection(Direction dir) { direction = dir; }

void ElevatorCar::setDisplay() {
    display->setCurrentFloor(currentFloor);
    display->setDirection(direction);
}

void ElevatorCar::setStatus(ElevatorStatus stat) { status = stat; }

void ElevatorCar::pressInnerButton(int floor) {
    innerButton->pressButton(floor, id);
}
