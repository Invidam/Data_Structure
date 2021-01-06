#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct _NODE NODE;
extern void Level_Traverse(NODE *ptrNode);
extern void Visit(NODE *);
extern int InsertNode(NODE **root,int Data);
extern int DeleteNode(NODE **root,int Data);
extern NODE *node_create(int key0, int key1, int key2);
extern void InitializeQueue(void);
extern void Put(NODE *);
extern NODE *Get(void);
extern int IsQueueEmpty(void);

#ifdef __cplusplus
}
#endif