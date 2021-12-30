#pragma once

///--------------------------------------------------------------------------------------
/// @file	CppStateTransitionInfo.h
/// @brief	classes to store and handle state transition information.
///
/// @author		Michael Roop
/// @date		2021
/// @version	1.0
///
/// Copyright 2021 Michael Roop
///--------------------------------------------------------------------------------------
namespace CppStateMachine {

#include "CppTransitionType.h"
#include <algorithm>

	/// <summary>Forward declaration of functor</summary>
	/// <typeparam name="T"></typeparam>
	template <class T> struct FindStateTransition;

	/// <summary>Forward declaration of CppState</summary>
	/// <typeparam name="T"></typeparam>
	template <class T> class CppState;

	/// <summary>Transition info class</summary>
	/// <typeparam name="T"></typeparam>
	template <class T>
	class CppStateTransitionInfo {
	public:
		/// <summary>Constructor</summary>
		/// <param name="id">Unique identifier for the transition</param>
		/// <param name="type">Type of transition</param>
		/// <param name="nextState">The next state to transition to</param>
		CppStateTransitionInfo(unsigned int id, TRANSITION_TYPE type, CppState<T>* nextState = NULL) :
			m_id(id),
			m_type(type),
			m_nextState(nextState)
		{}

		/// <summary>Either an event or result identifier</summary>
		unsigned int	m_id;

		/// <summary>Type of info</summary>
		unsigned int	m_type;

		/// <summary>Next state for transition</summary>
		CppState<T>* m_nextState;
	};


	//----------------------------------------------------------

	/// <summary>Functor to find if the transition is registered</summary>
	/// <typeparam name="T"></typeparam>
	template<class T>
	struct FindStateTransition {

		/// <summary>Constructor</summary>
		/// <param name="target">Target transition ID</param>
		FindStateTransition(unsigned int target) : m_target(target) {
		}

		bool operator ()(const CppStateTransitionInfo<T>& ti) const {
			return ti.m_id == m_target;
		}

		/// <summary>Target transition identifier</summary>
		unsigned int m_target;
	};

}