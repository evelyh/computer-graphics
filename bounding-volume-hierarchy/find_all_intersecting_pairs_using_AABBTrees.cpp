#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list>

void find_all_intersecting_pairs_using_AABBTrees(
    const std::shared_ptr<AABBTree> &rootA,
    const std::shared_ptr<AABBTree> &rootB,
    std::vector<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> &
        leaf_pairs)
{
  std::list<std::pair<std::shared_ptr<AABBTree>, std::shared_ptr<AABBTree>>> ll;

  if (box_box_intersect(rootA->box, rootB->box))
  {
    ll.emplace_back(rootA, rootB);
  }

  std::shared_ptr<AABBTree> tmp_a, tmp_b;

  // auto push_pairs = [](std::list<std::pair<std::shared_ptr<AABBTree>, std::shared_ptr<AABBTree>>> &ll,
  //                      std::shared_ptr<Object> &a, std::shared_ptr<Object> &b)
  // {
  //   ll.emplace_back(std::dynamic_pointer_cast<AABBTree>(a), std::dynamic_pointer_cast<AABBTree>(b));
  // };

  while (!ll.empty())
  {
    tmp_a = ll.front().first;
    tmp_b = ll.front().second;
    ll.pop_front();

    if (tmp_a->num_leaves > 1 && tmp_b->num_leaves > 1)
    {
      if (box_box_intersect(tmp_a->left->box, tmp_b->left->box))
        ll.emplace_back(std::dynamic_pointer_cast<AABBTree>(tmp_a->left), std::dynamic_pointer_cast<AABBTree>(tmp_b->left));
      // push_pairs(ll, tmp_a->left, tmp_b->left);
      if (box_box_intersect(tmp_a->left->box, tmp_b->right->box))
        ll.emplace_back(std::dynamic_pointer_cast<AABBTree>(tmp_a->left), std::dynamic_pointer_cast<AABBTree>(tmp_b->right));
      // push_pairs(ll, tmp_a->left, tmp_b->right);
      if (box_box_intersect(tmp_a->right->box, tmp_b->left->box))
        ll.emplace_back(std::dynamic_pointer_cast<AABBTree>(tmp_a->right), std::dynamic_pointer_cast<AABBTree>(tmp_b->left));
      // push_pairs(ll, tmp_a->right, tmp_b->left);
      if (box_box_intersect(tmp_a->right->box, tmp_b->right->box))
        ll.emplace_back(std::dynamic_pointer_cast<AABBTree>(tmp_a->right), std::dynamic_pointer_cast<AABBTree>(tmp_b->right));
      // push_pairs(ll, tmp_a->right, tmp_b->right);
    }
    else if (tmp_a->num_leaves <= 1 && tmp_b->num_leaves > 1)
    {
      if (box_box_intersect(tmp_a->box, tmp_b->left->box))
        ll.emplace_back(tmp_a, std::dynamic_pointer_cast<AABBTree>(tmp_b->left));
      if (box_box_intersect(rootA->box, rootB->right->box))
        ll.emplace_back(tmp_a, std::dynamic_pointer_cast<AABBTree>(tmp_b->right));
    }
    else if (tmp_a->num_leaves > 1 && tmp_b->num_leaves <= 1)
    {
      if (box_box_intersect(tmp_a->left->box, tmp_b->box))
        ll.emplace_back(std::dynamic_pointer_cast<AABBTree>(tmp_a->left), tmp_b);
      if (box_box_intersect(tmp_a->right->box, tmp_b->box))
        ll.emplace_back(std::dynamic_pointer_cast<AABBTree>(tmp_a->right), tmp_b);
    }
    else //(tmp_a->num_leaves <= 1 && tmp_b->num_leaves <= 1)
    {
      if (box_box_intersect(tmp_a->left->box, tmp_b->left->box))
        leaf_pairs.emplace_back(tmp_a->left, tmp_b->left);
    }
  }
}
