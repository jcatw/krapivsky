
namespace bignet {
  class TreeNode {
  public:
    TreeNode *left;
    TreeNode *right;
  };
  
  void rotate_left(TreeNode *& node);
  void rotate_right(TreeNode *& node);
}
