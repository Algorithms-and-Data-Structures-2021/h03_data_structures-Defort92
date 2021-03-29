#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

void LinkedDequeue::Enqueue(Element e) {
  DoublyNode *node = new DoublyNode(e, nullptr, back_);

  if (size_ == 0) {
      front_ = node;
  } else {
      back_ -> previous = node;
  }
  back_ = node;
  size_ += 1;
}

void LinkedDequeue::EnqueueFront(Element e) {
  DoublyNode *node = new DoublyNode(e, front_, nullptr);
  if (size_ == 0) {
      back_ = node;
  } else {
      front_ -> next = node;
  }
  front_ = node;
  size_ += 1;
}

void LinkedDequeue::Dequeue() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }

  DoublyNode *del_node = front_;
  front_ = front_ -> previous;

  if (front_ != nullptr) {
      front_ -> next = nullptr;
  } else {
      back_ = nullptr;
  }
  delete del_node;
  size_ -= 1;
}

void LinkedDequeue::DequeueBack() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }

  DoublyNode *del_node = back_;
  back_ = back_ -> next;

  if (back_ != nullptr) {
      back_ -> previous = nullptr;
  } else {
      front_ = nullptr;
  }
  delete del_node;
  size_ -= 1;
}

void LinkedDequeue::Clear() {
  DoublyNode *curr = back_;
  DoublyNode *del_node;
  while (curr != nullptr) {
      del_node = curr;
      curr = curr -> next;
      delete del_node;
  }
  front_ = nullptr;
  back_ = nullptr;
  size_ = 0;
}

// === РЕАЛИЗОВАНО ===

LinkedDequeue::~LinkedDequeue() {
  Clear();
}

std::optional<Element> LinkedDequeue::front() const {
  return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
}

std::optional<Element> LinkedDequeue::back() const {
  return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
}

bool LinkedDequeue::IsEmpty() const {
  return size_ == 0;
}

int LinkedDequeue::size() const {
  return size_;
}

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
  os << "size: " << queue.size_ << '\n';
  for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
    if (current_node == queue.front_) os << "[FRONT] ";
    if (current_node == queue.back_) os << "[BACK] ";
    os << enum2str(current_node->data) << '\n';
  }
  return os;
}

}  // namespace itis
