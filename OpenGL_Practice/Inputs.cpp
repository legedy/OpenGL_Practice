#include<iostream>
#include"Inputs.h"

Input::Input(GLFWwindow* window) {
	glfwSetWindowUserPointer(window, static_cast<void*>(this));
	glfwSetKeyCallback(window, _onKeyPress);
}

void Input::registerScroll(scrollCallback callback) {
	scrollCallbacks.push_back(callback);
}

void Input::registerMousePos(mouseMoveCallback callback) {
	scrollCallbacks.push_back(callback);
}

void Input::registerMouse(int button, mousePressCallback callback) {

	if (mousePressCallbacks.find(button) == mousePressCallbacks.end()) {
		std::vector<mousePressCallback> vector;
		vector.push_back(callback);

		mousePressCallbacks[button] = vector;
	} else {
		mousePressCallbacks[button].push_back(callback);
	}

}

void Input::registerKey(int key, keyPressCallback callback) {

	if (keyPressCallbacks.find(key) == keyPressCallbacks.end()) {
		std::vector<keyPressCallback> vector;
		vector.push_back(callback);

		keyPressCallbacks[key] = vector;
	}
	else {
		keyPressCallbacks[key].push_back(callback);
	}

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

void Input::onMousePress(GLFWwindow* window, int button, int state) {
	// If it finds the button id array, do (...)
	if (mousePressCallbacks.find(button) != mousePressCallbacks.end()) {
		for (mousePressCallback func : mousePressCallbacks[button]) {
			func(window, state);
		}
	}
}

void Input::onKeyPress(GLFWwindow* window, int key, int scancode, int state) {
	// If it finds the key id array, do (...)
	if (keyPressCallbacks.find(key) != keyPressCallbacks.end()) {
		for (keyPressCallback func : keyPressCallbacks[key]) {
			func(window, state);
		}
	}
}

// Handles all events and sends them to secondary methods
void Input::_onScroll(GLFWwindow* win, double xOffset, double yOffset) {
	Input* handler = static_cast<Input*>(glfwGetWindowUserPointer(win));

	if (handler) {
		handler->onScroll(win, xOffset, yOffset);
	} else handler->USER_POINTER_EXCEPTION();
}
void Input::_onMouseMoved(GLFWwindow* win, double xPos, double yPos) {
	Input* handler = static_cast<Input*>(glfwGetWindowUserPointer(win));

	if (handler) {
		handler->onMouseMoved(win, xPos, yPos);
	} else handler->USER_POINTER_EXCEPTION();
}
void Input::_onMousePress(GLFWwindow* win, int button, int action) {
	Input* handler = static_cast<Input*>(glfwGetWindowUserPointer(win));

	if (handler) {
		handler->onMousePress(win, button, action);
	} else handler->USER_POINTER_EXCEPTION();
}
void Input::_onKeyPress(GLFWwindow* win, int key, int scancode, int action, int mod) {
	Input* handler = static_cast<Input*>(glfwGetWindowUserPointer(win));

	if (handler) {
		handler->onKeyPress(win, key, scancode, action);
	} else handler->USER_POINTER_EXCEPTION();
}

void Input::USER_POINTER_EXCEPTION() {
	throw ("GLFW window user pointer not initialized.");
}