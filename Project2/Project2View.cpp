/*
수정사항 : 
1. -6 * -6 구현
2. 7.2!은 7!로 계산
3. 7.1.2는 7.12로 입력됨
4. e, 파이 값 리턴 버튼 생성
5. x^y 계산 버튼 생성
*/




// Project2View.cpp: CProject2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Project2.h"
#endif

#include "Project2Doc.h"
#include "Project2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProject2View

IMPLEMENT_DYNCREATE(CProject2View, CView)

BEGIN_MESSAGE_MAP(CProject2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CProject2View 생성/소멸

CProject2View::CProject2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

	button[0] = "%";
	button[1] = "|X|";
	button[2] = "C";
	button[3] = "<-";
	button[4] = "1/x";
	button[5] = "x²"; 
	button[6] = "n!";
	button[7] = "÷";
	button[8] = "7";
	button[9] = "8";
	button[10] = "9";
	button[11] = "X";
	button[12] = "4";
	button[13] = "5";
	button[14] = "6";
	button[15] = "-";
	button[16] = "1";
	button[17] = "2";
	button[18] = "3";
	button[19] = "+";
	button[20] = "+/-";
	button[21] = "0";
	button[22] = ".";
	button[23] = "=";
	button[24] = "e";
	button[25] = "π";
	button[26] = "x^y";

}

CProject2View::~CProject2View()
{
}

BOOL CProject2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	//cs.cx = 3000, cs.cy = 300;

	return CView::PreCreateWindow(cs);
}

// CProject2View 그리기

void CProject2View::OnDraw(CDC* /*pDC*/)
{
	CProject2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);
	CRect rc;
	GetClientRect(&rc);
	int right = rc.right;
	int bottom = rc.bottom;
	space_right = rc.right / 4;
	space_bottom = (rc.bottom - 300) / 7;
	str.Format(_T("%.2f"), result);
	str2.Format(_T("%.2f"), click_value);

	CFont font1, font2;
	dc.SetBkMode(TRANSPARENT);
	font1.CreatePointFont(500, _T("Time New Romans"));
	dc.SelectObject(&font1);
	dc.DrawText(str2, CRect(0, 0, rc.right, 100), DT_TOP | DT_SINGLELINE | DT_RIGHT | DT_VCENTER);
	font2.CreatePointFont(800, _T("Time New Romans"));
	dc.SelectObject(&font2);
	dc.DrawText(str, CRect(0,160,rc.right,260), DT_TOP | DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	Interface_init();
}


// CProject2View 인쇄

BOOL CProject2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CProject2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CProject2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CProject2View 진단

#ifdef _DEBUG
void CProject2View::AssertValid() const
{
	CView::AssertValid();
}

void CProject2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProject2Doc* CProject2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProject2Doc)));
	return (CProject2Doc*)m_pDocument;
}
#endif //_DEBUG


// CProject2View 메시지 처리기


void CProject2View::Interface_init()
{
	// TODO: 여기에 구현 코드 추가.

	CClientDC dc(this);

	//파란 부분 출력되는 = 부분
	button_count = 23;
	if (button_color_equal == 0) {
		CBrush brush2(RGB(138, 186, 224));
		dc.SelectObject(&brush2);
		dc.Rectangle(space_right * 3, 300 + space_bottom * 5, space_right*(3 + 1), 300 + space_bottom * (5 + 2));
	}
	else if (button_color_equal == 1) {
		CBrush brush2(RGB(0, 120, 215));
		dc.SelectObject(&brush2);
		dc.Rectangle(space_right * 3, 300 + space_bottom * 5, space_right*(3 + 1), 300 + space_bottom * (5 + 2));
	}
	dc.SetBkMode(TRANSPARENT);
	TextOut(dc, space_right * 3 + space_right / 2, 300 + space_bottom * 5 + space_bottom, button[button_count], lstrlen(button[button_count]));


	//흰색으로 출력되는 숫자와 +/-, . 부분 
	button_count = 8;
	for (int j = 2; j < 6; j++) {
		for (int i = 0; i < 3; i++) {
			if (button_color_num[(i + (j - 2)) + 2 * (j - 2)] == 0) {
				CBrush brush1(RGB(255, 255, 255));
				dc.SelectObject(&brush1);
				dc.Rectangle(space_right*i, 300 + space_bottom * j, space_right*(i + 1), 300 + space_bottom * (j + 1));
			}
			if (button_color_num[(i+(j-2))+2*(j-2)] == 1) {
				CBrush brush1(RGB(187, 187, 187));
				dc.SelectObject(&brush1);
				dc.Rectangle(space_right*i, 300 + space_bottom * j, space_right*(i + 1), 300 + space_bottom * (j + 1));
			}
			TextOut(dc, space_right*i + space_right / 2, 300 + space_bottom * j + space_bottom / 2, button[button_count], lstrlen(button[button_count]));
			button_count++;
		}
		button_count++;
	}

	//회색으로 출력되는 연산자 부분
	button_count = 0;
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 3; i++) {
			if (button_color_symbol[(i + j * 3)] == 0) {
				CBrush brush3(RGB(240, 240, 240));
				dc.SelectObject(&brush3);
				dc.Rectangle(space_right*i, 300 + space_bottom * j, space_right*(i + 1), 300 + space_bottom * (j + 1));
			}
			else if (button_color_symbol[(i + j * 3)] == 1) {
				CBrush brush3(RGB(187, 187, 187));
				dc.SelectObject(&brush3);
				dc.Rectangle(space_right*i, 300 + space_bottom * j, space_right*(i + 1), 300 + space_bottom * (j + 1));
			}
			TextOut(dc, space_right*i + space_right / 2, 300 + space_bottom * j + space_bottom / 2, button[button_count], lstrlen(button[button_count]));
			button_count++;
		}
		button_count ++;
	}
	button_count = 3;
	for (int j = 0; j < 5; j++) {
		if (button_color_symbol[6 + j] == 0) {
			CBrush brush3(RGB(240, 240, 240));
			dc.SelectObject(&brush3);
			dc.Rectangle(space_right * 3, 300 + space_bottom * j, space_right*(3 + 1), 300 + space_bottom * (j + 1));
		}
		else if (button_color_symbol[6 + j] == 1) {
			CBrush brush3(RGB(187, 187, 187));
			dc.SelectObject(&brush3);
			dc.Rectangle(space_right * 3, 300 + space_bottom * j, space_right*(3 + 1), 300 + space_bottom * (j + 1));
		}
		TextOut(dc, space_right * 3 + space_right / 2, 300 + space_bottom * j + space_bottom / 2, button[button_count], lstrlen(button[button_count]));
		button_count += 4;
	}

	button_count = 24;//번호키 하단부분
	for (int i = 0; i < 3; i++) {
		if (button_color_symbol[11 + i] == 0) {
			CBrush brush3(RGB(240, 240, 240));
			dc.SelectObject(&brush3);
			dc.Rectangle(space_right*i, 300 + space_bottom * 6, space_right*(i + 1), 300 + space_bottom * 7);
		}
		else if (button_color_symbol[11 + i] == 1) {
			CBrush brush3(RGB(187, 187, 187));
			dc.SelectObject(&brush3);
			dc.Rectangle(space_right*i, 300 + space_bottom * 6, space_right*(i + 1), 300 + space_bottom * 7);
		}
		TextOut(dc, space_right * i + space_right / 2, 300 + space_bottom * 6 + space_bottom / 2, button[button_count], lstrlen(button[button_count]));
		button_count++;
	}
}


void CProject2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// = 키를 진한 파란색으로 
	if (point.x > space_right * 3 && point.y > 300 + space_bottom * 5) {
		button_color_equal = 1;
		calculate();
	}

	//번호키를 회색으로
	for (int i = 0; i < 3; i++) {
		if (point.x > (space_right * i) && point.x < (space_right * (i + 1))) {
			for (int j = 0; j < 4; j++)
				if (point.y > 300 + space_bottom * (2 + j) && point.y < 300 + space_bottom * (3 + j)) {
					button_color_num[j * 3 + i] = 1;
					if (j == 3 && i == 0) { // +/-
						click_value = -click_value;
						result = click_value;
					}
					else if (j == 3 && i == 1) { // 0
						double buffer = click_value;
						click_value = (buffer * 10) + 0;
					}
					else if (j == 3 && i == 2) { // .
						sosu = TRUE;
					}
					else { // 숫자 넣기
						double buffer = click_value;
						if (sosu == TRUE) {
							if (minus == FALSE) {
								click_value = buffer + (sosu_count * 0.1 * (7 + i - j * 3));
								sosu_count *= 0.1;
							}
							else if (minus == TRUE) {
								click_value = buffer - (sosu_count * 0.1 * (7 + i - j * 3));
								sosu_count *= 0.1;
							}
						}
						else if(sosu == FALSE){
							if (minus == FALSE) {
								click_value = (buffer * 10) + 7 + i - j * 3;
							}
							else if (minus == TRUE) {
								click_value = (buffer * 10) - (7 + i - j * 3);
							}
						}
					}
				}
		}
	}

	//연산키를 진한 회색으로
	for (int j = 0; j < 3; j++) {
		if (point.x > (space_right * j) && point.x < (space_right * (j + 1))) {
			for (int i = 0; i < 2; i++) {
				if (point.y > 300 + space_bottom * (i) && point.y < 300 + space_bottom * (1 + i)) {
					button_color_symbol[i * 3 + j] = 1;
					symbol_value = i * 3 + j;
					//0은 나머지, 1은 절대값, 3은 역수, 5는 팩토리얼
					if (symbol_value == 0) { // 나머지
						click_value_buffer = click_value;
						click_value = 0;
						sosu = FALSE;
					}
					else if (symbol_value == 1) { // 절댓값
						if (click_value < 0) {
							click_value = -click_value;
							result = click_value;
						}
						else
							result = click_value;
					}
					else if (symbol_value == 2) { // C를 누르면 초기화
						click_value = 0;
						click_value_buffer = 0;
						result = 0;
						sosu = FALSE;
						minus = FALSE;
						sosu_count = 1;
					}
					else if (symbol_value == 3) { // 1/x
						result = 1.0 / click_value;
						click_value = result;
					}
					else if (symbol_value == 4) { //제곱계산
						result = click_value * click_value;
						click_value = result;
					}
					else if (symbol_value == 5) { // 팩토리얼
						//팩토리얼은 그 수보다 작거나 같은 모든 양의 정수의 곱.
						//실수값이 들어올 경우 실수를 정수로 바꾼 후 팩토리얼 시행.
						int count = click_value;
						if (count < 0) {
							count = -count;
						}// -3! = -6
						for (int i = count - 1; i > 0; i--) {
							click_value = (int)click_value * i;
						}
						result = click_value;
					}


				}
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (point.x > space_right * 3) {
			if (point.y > space_bottom*(i)+300 && point.y < space_bottom * (i + 1) + 300) {
				button_color_symbol[i + 6] = 1;
				symbol_value = i + 6; 
				if (symbol_value == 6) { //6 = 지우기
					int c = click_value;
					c = c / 10;
					click_value = c;
					sosu = FALSE;
					minus = FALSE;
					// 5 다음 6을 넣었을 때 56을 만들 수 있음
				}
				// 10 = +, 9 = -, 8 = X, 7 = /
				else if (symbol_value == 10 || symbol_value == 8 || symbol_value == 7) {
					click_value_buffer = click_value;
					click_value = 0.0;
					sosu = FALSE;
					sosu_count = 1;
					minus = FALSE;
					symbol_value_buffer = symbol_value;
				}
				else if (symbol_value == 9) {
					minus = TRUE;
					if (symbol_value_buffer == 0) {
						click_value_buffer = click_value;
						click_value = 0.0;
						sosu = FALSE;
						sosu_count = 1;
						symbol_value = 10;
					}
					else {
						symbol_value = symbol_value_buffer;
					}
				}
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		if (point.x > (space_right * i) && point.x < (space_right * (i + 1))) {
			if (point.y > 300 + space_bottom * 6 && point.y < 300 + space_bottom * 7) {
				button_color_symbol[i + 11] = 1;
				symbol_value = i + 11;
				if (symbol_value == 11) { // e
					result = 2.71;
					click_value = result;
				}
				else if (symbol_value == 12) { // 파이
					result = 3.14;
					click_value = result;
				}
				else if (symbol_value == 13) { // x^y
					click_value_buffer = click_value;
					click_value = 0.0;
					minus = FALSE;
				}
			}
		}
	}

	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CProject2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	button_color_equal = 0;

	for (int i = 0; i < 12; i++) {
		button_color_num[i] = 0 ;
	}

	for (int i = 0; i < 14; i++) {
		button_color_symbol[i] = 0;
	}

	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


double CProject2View::calculate()
{
	// TODO: 여기에 구현 코드 추가.
	if (symbol_value == 10 || symbol_value == 9) { // 더하기, 빼기
		result = click_value_buffer + click_value;
		click_value = result;
	}
	else if (symbol_value == 8) { // 곱하기
		result = click_value_buffer * click_value;
		click_value = result;
	}
	else if (symbol_value == 7) { // 나누기
		result = click_value_buffer / click_value;
		click_value = result;
	}
	else if (symbol_value == 0) { // 나머지
		int a = click_value_buffer;
		int b = click_value;
		result = a % b;
		click_value = result;
	}
	else if (symbol_value == 13) { // x의 y승
		int num = click_value_buffer;
		for (int i = 1; i < (int)click_value; i++) {
			click_value_buffer = click_value_buffer * num;
		}
		result = click_value_buffer;
	}
	if (result == -0.0) {
		result = 0.0;
	}
	symbol_value_buffer = 0;
	minus = FALSE;
	return result;
}


void CProject2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	if (nChar == 0x30 || nChar == VK_NUMPAD0) {
		double buffer = click_value;
		if (sosu == TRUE) {
			click_value = buffer + (sosu_count * 0.1 * 0);
			sosu_count *= 0.1;
		}
		else if (sosu == FALSE) {
			click_value = (buffer * 10) + 0;
		}
	}
	else if (nChar == 0x31 || nChar == VK_NUMPAD1) {
		double buffer = click_value;
		if (sosu == TRUE) {
			click_value = buffer + (sosu_count * 0.1 * 1);
			sosu_count *= 0.1;
		}
		else if (sosu == FALSE) {
			click_value = (buffer * 10) + 1;
		}
	}
	else if (nChar == 0x32 || nChar == VK_NUMPAD2) {
		double buffer = click_value;
		if (sosu == TRUE) {
			click_value = buffer + (sosu_count * 0.1 * 2);
			sosu_count *= 0.1;
		}
		else if (sosu == FALSE) {
			click_value = (buffer * 10) + 2;
		}
	}
	else if (nChar == 0x33 || nChar == VK_NUMPAD3) {
		double buffer = click_value;
		if (sosu == TRUE) {
			click_value = buffer + (sosu_count * 0.1 * 3);
			sosu_count *= 0.1;
		}
		else if (sosu == FALSE) {
			click_value = (buffer * 10) + 3;
		}
	}
	else if (nChar == 0x34 || nChar == VK_NUMPAD4) {
		double buffer = click_value;
		if (sosu == TRUE) {
			click_value = buffer + (sosu_count * 0.1 * 4);
			sosu_count *= 0.1;
		}
		else if (sosu == FALSE) {
			click_value = (buffer * 10) + 4;
		}
	}
	else if (nChar == 0x35 || nChar == VK_NUMPAD5) {
		double buffer = click_value;
		if (sosu == TRUE) {
			click_value = buffer + (sosu_count * 0.1 * 5);
			sosu_count *= 0.1;
		}
		else if (sosu == FALSE) {
			click_value = (buffer * 10) + 5;
		}
	}
	else if (nChar == 0x36 || nChar == VK_NUMPAD6) {
		double buffer = click_value;
		if (sosu == TRUE) {
			click_value = buffer + (sosu_count * 0.1 * 6);
			sosu_count *= 0.1;
		}
		else if (sosu == FALSE) {
			click_value = (buffer * 10) + 6;
		}
	}
	else if (nChar == 0x37 || nChar == VK_NUMPAD7) {
		double buffer = click_value;
		if (sosu == TRUE) {
			click_value = buffer + (sosu_count * 0.1 * 7);
			sosu_count *= 0.1;
		}
		else if (sosu == FALSE) {
			click_value = (buffer * 10) + 7;
		}
	}
	else if (nChar == 0x38 || nChar == VK_NUMPAD8) {
		double buffer = click_value;
		if (sosu == TRUE) {
			click_value = buffer + (sosu_count * 0.1 * 8);
			sosu_count *= 0.1;
		}
		else if (sosu == FALSE) {
			click_value = (buffer * 10) + 8;
		}
	}
	else if (nChar == 0x39 || nChar == VK_NUMPAD9) {
		double buffer = click_value;
		if (sosu == TRUE) {
			click_value = buffer + (sosu_count * 0.1 * 9);
			sosu_count *= 0.1;
		}
		else if (sosu == FALSE) {
			click_value = (buffer * 10) + 9;
		}
	}
	else if (nChar == VK_OEM_PERIOD) { // .
		sosu = TRUE;
	}

	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
