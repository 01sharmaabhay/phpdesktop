//
// ClickEvents.h
// Copyright (c) Czarek Tomczak. All rights reserved.
//

#pragma once

// See "SubmitEvents.h" for explanation in English.

/*
	Wykrywanie przejscia na nowa strone w przegladarce i w razie
	potrzeby blokowanie zewn�trznych linkow ktore probuja sie odpalic
	w oknie przegladarki, dla nich osobne wywolanie systemowe "start http://".

	DWebBrowserEvents2::BeforeNavigate2 - nie jeste�my w stanie rozr�ni�, czy
		url wgrywany to nowy url dla danego okna czy url dla skryptu czy obrazka.

	Jest opcja, �eby podpi�� si� pod event "onunload" - jest on wywolywane tuz przed
	opuszczeniem strony - i je�eli BeforeNavigate2 odpala si� po onunload to 
	mogliby�my to wykorzysta� i by� pewni �e to g��wne okno przegl�darki zmienia
	lokacj�, a nie jaki� skypt, styl css czy obrazek.

	Podpi�� pod "onunload" event mo�emy wykorzystuj�c:
		
	IHTMLWindow2::put_onunload(VARIANT p)
	IHTMLWindow3::attachEvent(BSTR event, IDispatch *pDisp, VARIANT_BOOL *pfResult)

	Jak pobra� IHTMLWindow?
	IWebBrowser2::get_document() => IHTMLDocument2::get_parentWindow()

	Sprawd� czy w BeforeNavigate2 w "headers" nie ma przypadkiem informacji, kt�r�
	mo�na by zidentyfikowa� r�nego typu nawigacje: czy to skrypt, czy css, czy
	g��wne okno przegl�darki.

	----

	Zr�b attachEvent na evencie "click" w ten spos�b wy�apiesz wszystkie kliki na 
	linkach, sprawdzisz czy zewn�trzny, je�li tak to nie pozwolisz na odpalenie
	go w oknie przegl�darki, lecz wywolasz zewn�trzne polecenie "start http://".
	
	Dodatkowo trzeba wychwyci� wszelkie wywo�ania "window.location", trzeba te�
	je kontrolowa�.
	
	- sprawd� czy ten attachEvent dla click wychwytuje te� clicki w iframie, bo
		w iframie pozwalamy na nawigacj� po zewn�trznych stronach.

	Jak pobra� IHTMLWindow3:
	1. IWebBrowser2->getdocument
	2. IHTMLDocument2->get_parentWindow
	3. HTMLWindow2->QueryInterface(IHTMLWindow3)

	Przyk�ad attachEvent:
	(http://webcache.googleusercontent.com/search?hl=pl&q=cache%3Ahttps%3A%2F%2Fforums.embarcadero.com%2Fthread.jspa%3FthreadID%3D18052%26tstart%3D4)

	CComBSTR onScrollName( TEXT( "onscroll" ) );
	VARIANT_BOOL result = VARIANT_TRUE;
	hr = window3->attachEvent( onScrollName, events, &result );
	if ( result != VARIANT_TRUE ) {}

	class Events : public IDispatch{
		GetTypeInfoCount : E_NOTIMPL
		GetTypeInfo : E_NOTIMPL
		GetIDsOfNames : E_NOTIMPL
		
		STDMETHODIMP CIE4Events::Invoke(DISPID dispidMember, REFIID riid, LCID 
		lcid, WORD wFlags, DISPPARAMS* pDispParams, VARIANT* pvarResult,
		EXCEPINFO* pExcepInfo, UINT* puArgErr)
		{
			if ( !pDispParams ) {
			return E_INVALIDARG;
			}
			if ( _browserControl != NULL &&
			pDispParams->cArgs == 1 && pDispParams->rgvarg [0].vt == 
			VT_DISPATCH ) {

			ComPtrQI <IHTMLEventObj > event( ComPtrQI <IDispatch> ( 
			pDispParams->rgvarg [0].pdispVal ) );

			if ( event ) {

			event IHTMLEventObj::get_srcElement(IHTMLElement **p);
			
			event IHTMLEventObj::put_returnValue(VARIANT v)
			false	Default action of the event on the source object is canceled.

		}

	}

	IDispEventSimpleImpl:
	http://gears.googlecode.com/svn/trunk/gears/base/common/html_event_monitor_ie.cc

*/

class ClickEvents : public IDispatch
{
public:
	ClickEvents(){}

	// IDispatch


};
