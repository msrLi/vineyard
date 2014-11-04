#ifndef _TASK_GUI_H_
#define _TASK_GUI_H_
#include"includes.h"
#include"EmWinAllHeader.h"
void AppTaskGUI(void *p_arg);          // 创建任务
void AppTaskGUIRefresh(void *p_arg);   // 刷新任务
void AppTaskGUIDrawing(void *p_arg);   // 画图刷新函数
#endif
