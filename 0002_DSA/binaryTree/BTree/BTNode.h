/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2019. All rights reserved.
 ******************************************************************************************/

#pragma once

#include <vector>
#define BTNodePosi(T) BTNode<T>* //B-���ڵ�λ��

template <typename T> struct BTNode { //B-���ڵ�ģ����
// ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ��
   BTNodePosi(T) parent; //���ڵ�
   vector<T> key; //�ؼ�������
   vector<BTNodePosi(T)> child; //�����������䳤���ܱ�key��һ��
// ���캯����ע�⣺BTNodeֻ����Ϊ���ڵ㴴�������ҳ�ʼʱ��0���ؼ����1���պ���ָ�룩
   BTNode() { parent = NULL; child.insert ( child.begin(), NULL ); }
   BTNode ( T e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL ) {
      parent = NULL; //��Ϊ���ڵ㣬���ҳ�ʼʱ
      //key.insert ( 0, e ); //ֻ��һ���ؼ��룬�Լ�
      key.push_back(e);
      //child.insert ( 0, lc ); child.insert ( 1, rc ); //��������
      child.push_back(lc);child.push_back(rc);
      if ( lc ) lc->parent = this; if ( rc ) rc->parent = this;
   }
   /*
   BTNode() { parent = NULL; child.insert ( 0, NULL ); }
   BTNode ( T e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL ) {
      parent = NULL; //��Ϊ���ڵ㣬���ҳ�ʼʱ
      key.insert ( 0, e ); //ֻ��һ���ؼ��룬�Լ�
      child.insert ( 0, lc ); child.insert ( 1, rc ); //��������
      if ( lc ) lc->parent = this; if ( rc ) rc->parent = this;
   }
   */
};