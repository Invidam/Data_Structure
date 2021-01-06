#pragma once

#ifdef __cplusplus
extern "C" {
#endif
typedef struct _NODE NODE;
extern void Level_Traverse(NODE *ptrNode);
extern void Visit(NODE *);
extern NODE *InsertNode(NODE *root,int key);
extern NODE *DeleteNode(NODE *root,int key);
extern void InitializeQueue(void);
extern void Put(NODE *);
extern NODE *Get(void);
extern int IsQueueEmpty(void);

#ifdef __cplusplus
}
#endif

