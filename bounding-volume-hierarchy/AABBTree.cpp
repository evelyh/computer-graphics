#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
    const std::vector<std::shared_ptr<Object>> &objects,
    int a_depth) : depth(std::move(a_depth)),
                   num_leaves(objects.size())
{

  for (auto &obj : objects)
  {
    insert_box_into_box(obj->box, this->box);
  }

  if (num_leaves < 3)
  {
    if (num_leaves > 0)
      this->left = objects[0];
    if (num_leaves == 2)
      this->right = objects[1];

    if (num_leaves < 2)
      this->right = nullptr;
    if (num_leaves == 0)
      this->left = nullptr;
  }
  else
  {
    Eigen::RowVector3d diff = this->box.max_corner - this->box.min_corner;
    int axis;
    diff.maxCoeff(&axis);
    double mid = this->box.center()[axis];
    // partition A into lists with lengths k and (N − k) surrounding m
    std::vector<std::shared_ptr<Object>> left_tree, right_tree;

    for (auto &obj : objects)
    {
      if (obj->box.center()[axis] <= mid)
      {
        left_tree.emplace_back(obj);
      }
      else // if (obj->box.center()[axis] > mid)
      {
        right_tree.emplace_back(obj);
      }
    }

    if (left_tree.empty())
    {
      left_tree.emplace_back(right_tree.back());
      right_tree.pop_back();
    }
    if (right_tree.empty())
    {
      right_tree.emplace_back(left_tree.back());
      left_tree.pop_back();
    }

    this->left = std::make_shared<AABBTree>(AABBTree(left_tree, depth + 1));
    this->right = std::make_shared<AABBTree>(AABBTree(right_tree, depth + 1));
  }
}
