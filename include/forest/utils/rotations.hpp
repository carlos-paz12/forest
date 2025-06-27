#ifndef ROTATIONS_HPP
#define ROTATIONS_HPP
#include "../tree.hpp"
#endif //<! ROTATIONS_HPP


/**
 * @brief  Calculates the height of a node in the binary search tree.
 * 
 * @param node  Pointer to the node whose height is to be calculated.
 * @return value_type  The height of the node, or -1 if the node is null.
 */
value_type height_no(TreeNodePtr node){
    return (node == nullptr ? -1 : node->height); //!< Returns the height of the node or -1 if the node is null.
}

/**
 * @brief  Calculates the balance factor of a node in the binary search tree.
 * 
 * @param node  Pointer to the node whose balance factor is to be calculated.
 * @return value_type  The balance factor of the node, which is the difference between the heights of the left and right subtrees.
 */
value_type balance_factor(TreeNodePtr node) {
    return height_no(node->m_left) - height_no(node->m_right); //!< Calculates the balance factor of the node.
}

/**
 * @brief  Performs a single left rotation on the subtree rooted at the given node.
 * 
 * @param node  Reference to the pointer to the root of the subtree.
 * @return TreeNodePtr  Pointer to the new root of the subtree after rotation.
 */
TreeNodePtr r_simple_left(TreeNodePtr &node){
  if (node == nullptr || node->m_left == nullptr) return node; // Protege contra ponteiros nulos

  auto temp{ node->m_left }; //!< Temporary pointer to the left child of the root.
  node->m_left = temp->m_right; //!< Rotates the left subtree to the right.
  temp->m_right = node; //!< Sets the root as the right child of the temporary node.
  node->height = std::max(height_no(node->m_left), height_no(node->m_right)) + 1; //!< Updates the height of the root.
  temp->height = std::max(height_no(temp->m_left), height_no(temp->m_right)) + 1; //!< Updates the height of the temporary node.
  node = temp; //!< Updates the root to the temporary node.
    return node; //!< Returns the new root of the subtree.
}

/**
 * @brief  Performs a single right rotation on the subtree rooted at the given node.
 * 
 * @param node  Reference to the pointer to the root of the subtree.
 * @return TreeNodePtr  Pointer to the new root of the subtree after rotation.
 */
TreeNodePtr r_simple_right(TreeNodePtr &node){
  if (node == nullptr || node->m_right == nullptr) return node; // Protege contra ponteiros nulos
  auto temp{ node->m_right }; //!< Temporary pointer to the right child of the root.
  node->m_right = temp->m_left; //!< Rotates the right subtree to the left.
  temp->m_left = node; //!< Sets the root as the left child of the temporary node.
  node->height = std::max(height_no(node->m_left), height_no(node->m_right)) + 1; //!< Updates the height of the root.
  temp->height = std::max(height_no(temp->m_left), height_no(temp->m_right)) + 1; //!< Updates the height of the temporary node.
  node = temp; //!< Updates the root to the temporary node.
    return node; //!< Returns the new root of the subtree.
}

/**
 * @brief  Performs a double left rotation on the subtree rooted at the given node.
 * 
 * @param node  Reference to the pointer to the root of the subtree.
 * @return TreeNodePtr  Pointer to the new root of the subtree after rotation.
 */
TreeNodePtr r_double_left(TreeNodePtr &node){
  node->m_left = r_simple_right(node->m_left); //!< Performs a right rotation on the left child of the root.
  return r_simple_left(node); //!< Performs a left rotation
}

/**
 * @brief  Performs a double right rotation on the subtree rooted at the given node.
 * 
 * @param node  Reference to the pointer to the root of the subtree.
 * @return TreeNodePtr  Pointer to the new root of the subtree after rotation.
 */
TreeNodePtr r_double_right(TreeNodePtr &node){
  node->m_right = r_simple_left(node->m_right); //!< Performs a left rotation
  return r_simple_right(node); //!< Performs a right rotation on the root.
}