/**
 * @file stack.cpp
 * Implementation of the Stack class.
 *
 */

/**
 * Adds the parameter object to the top of the Stack.
 *
 * @param newItem object to be added to the Stack.
 */
template <class T>
void Stack<T>::push(T newItem) {
    data.push_back(newItem);
}

/**
 * Removes the object at the top of the Stack, and returns it to the
 * caller.
 *
 * @return The item that used to be at the top of the Stack.
 */
template <class T>
T Stack<T>::pop() {
    T result = peek();
    data.pop_back();
    return result;
}

/**
 * Finds the object at the top of the Stack, and returns it to the
 * caller. Unlike pop(), this operation does not alter the stack.
 *
 * @return The item at the top of the stack.
 */
template <class T>
T Stack<T>::peek() {
    return data[data.size()-1];
}

/**
 * Determines if the Stack is empty.
 *
 * @return bool which is true if the Stack is empty, false otherwise.
 */
template <class T>
bool Stack<T>::isEmpty() const {
    return (data.empty());
}
