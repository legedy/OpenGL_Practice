#include "Inputs.h"

Input::Input(GLFWwindow* window) {
	glfwSetWindowUserPointer(window, static_cast<void*>(this));
}

void Input::registerScroll(scrollCallback callback) {
	scrollCallbacks.push_back(callback);
}

void Input::registerMousePos(mouseMoveCallback callback) {
	scrollCallbacks.push_back(callback);
}

void Input::registerMouse(int button, mousePressCallback callback) {
	mousePressCallbacks.push_back({1, callback});
}

void Input::registerKey(int key, keyPressCallback callback) {
	keyPressCallbacks.push_back({1, callback});
}

// Secondary methods which 
void Input::onScroll(GLFWwindow* window, double x, double y) {
	for (scrollCallback func : scrollCallbacks) {
		func(window, x, y);
	}
}

void Input::onMouseMoved(GLFWwindow* window, double x, double y) {
	for (mouseMoveCallback func : mouseMoveCallbacks) {
		func(window, x, y);
	}
}

void Input::onMousePress(GLFWwindow* window, int state) {

}

void Input::onKeyPress(GLFWwindow* window, int state) {

}

// Handles all events and sends them to secondary methods
void Input::_onScroll(GLFWwindow* win, double xOffset, double yOffset) {
	Input* handler = static_cast<Input*>(glfwGetWindowUserPointer(win));

	if (handler) {
		handler->onScroll(win, xOffset, yOffset);
	} else {
		throw ("GLFW window user pointer not initialized.");
	}
}
void Input::_onMouseMoved(GLFWwindow* win, double xPos, double yPos) {

}
void Input::_onMousePress(GLFWwindow* win, int button, int action, int mods) {

}
void Input::_onKeyPress(GLFWwindow* win, int key, int scancode, int action, int mods) {

}