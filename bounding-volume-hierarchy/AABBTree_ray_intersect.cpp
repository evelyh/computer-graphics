#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
    const Ray &ray,
    const double min_t,
    const double max_t,
    double &t,
    std::shared_ptr<Object> &descendant) const
{
  if (ray_intersect_box(ray, this->box, min_t, max_t))
  {
    std::shared_ptr<Object> left_tree, right_tree;
    double left_t, right_t;

    bool left_hit = this->left && this->left->ray_intersect(ray, min_t, max_t, left_t, left_tree);
    if (!left_tree && left_hit)
      left_tree = this->left;

    bool right_hit = this->right && this->right->ray_intersect(ray, min_t, max_t, right_t, right_tree);
    if (!right_tree && right_hit)
      right_tree = this->right;

    if (left_hit && right_hit)
    {
      t = std::min(left_t, right_t);
      descendant = (left_t < right_t) ? left_tree : right_tree;
      return true;
    }
    else if (left_hit && !right_hit)
    {
      t = left_t;
      descendant = left_tree;
      return true;
    }
    else if (right_hit && !left_hit)
    {
      t = right_t;
      descendant = right_tree;
      return true;
    }
  }
  return false;
}
