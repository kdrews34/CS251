bst_node *_get_ith(int ith, bst_node *tmp)
  {

    if (tmp == nullptr)
    {
      return nullptr;
    }

    if (tmp->size_L + 1 == ith) // if I'th is the root in the search
    {
      return tmp;
    }

    else if (tmp->size_L + 1 > ith) // if I'TH is in the left subtree
    {
      return _get_ith(ith, tmp->left);
    }
    else
    {
      return _get_ith((ith - (tmp->size_L + 1)), tmp->right); //if (tmp->size_R + 1 < ith)
    }
    //else return nullptr;
  }

  bool get_ith(int i, T &x)
  {
    //bst_node *tmp = root; numnodes - position x (geq /////)

    if (i > (root->size_L + root->size_R + 1))
    {
      return false;
    }

    bst_node *tmp2 = _get_ith(i, root);

    if (tmp2 == nullptr) //|| i < 1)// ( i > (tmp2->size_L+tmp2->size_R + 1)) ||
    {
      return false;
    }
    else
    {
      x = tmp2->val;
      return true;
    }
    // placeholder
  }