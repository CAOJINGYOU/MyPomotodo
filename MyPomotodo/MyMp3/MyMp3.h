#pragma once

#include "dshow.h"

class  CMyMp3
{
public:
	CMyMp3(void);
	~CMyMp3(void);

public:
	IGraphBuilder *m_pGrap;
	IMediaControl *m_pControl;
	IMediaEvent *m_pEnvent;
public:
	bool m_bInitSuce;
	bool Init(void);
	bool Run(void);
};

