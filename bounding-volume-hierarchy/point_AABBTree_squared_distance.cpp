#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <limits>

typedef std::pair<double, std::shared_ptr<Object>> obj_pair;

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d &query,
    const std::shared_ptr<AABBTree> &root,
    const double min_sqrd,
    const double max_sqrd,
    double &sqrd,
    std::shared_ptr<Object> &descendant)
{
  sqrd = std::numeric_limits<double>::infinity();
  std::priority_queue<obj_pair, std::vector<obj_pair>, std::greater<obj_pair>> queue;

  queue.push(std::make_pair(point_box_squared_distance(query, root->box), root));

  obj_pair curr;
  std::shared_ptr<AABBTree> curr_ptr;
  while (!queue.empty())
  {
    curr = queue.top();
    queue.pop();

    if (curr.first < sqrd)
    {
      curr_ptr = std::dynamic_pointer_cast<AABBTree>(curr.second);
      if (curr_ptr != nullptr)
      {
        if (curr_ptr->left != nullptr)
        {
          queue.push(obj_pair(point_box_squared_distance(query, curr_ptr->left->box), curr_ptr->left));
        }
        if (curr_ptr->right != nullptr)
        {
          queue.push(obj_pair(point_box_squared_distance(query, curr_ptr->right->box), curr_ptr->right));
        }
      }
      else // curr_ptr == nullptr
      {
        double dist = point_box_squared_distance(query, curr.second->box);
        if (dist < sqrd)
        {
          sqrd = dist;
          descendant = curr.second;
          return true;
        }
      }
    }
  }
  return false;
}
