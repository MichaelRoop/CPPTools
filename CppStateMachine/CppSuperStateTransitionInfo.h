#pragma once

/// <summary>
/// 
/// CppStateTransitionInfo.h
/// classes to store and handle super state transition information.
///
/// author		Michael Roop
/// date		2021
/// version		1.0
///
/// Copyright 2021 Michael Roop
/// 
/// </summary>
namespace CppStateMachine {

	/// <summary>Forward declaration of functor</summary>
	/// <typeparam name="T"></typeparam>
	template <class T> struct FindSuperStateTransition;

	/// <summary>Forward declaration of CppState</summary>
	/// <typeparam name="T"></typeparam>
	template <class T> class CppState;


	template <class T> class CppSuperStateTransitionInfo {
	public:

		/// <summary>Constructor</summary>
		/// <param name="stateId"></param>
		/// <param name="result"></param>
		/// <param name="nextState"></param>
		CppSuperStateTransitionInfo(
			unsigned int stateId,
			unsigned int result,
			mr_state<T>* nextState) :
			m_stateId(id),
			m_result(result),
			m_nextState(nextState)
		{}

		/// <summary>The current sub state</summary>
		unsigned int	m_stateId;

		/// <summary>The result returned from the sub state</summary>
		unsigned int	m_result;

		/// <summary>Next state for transition</summary>
		CppState<T>* m_nextState;
	};


	//----------------------------------------------------------

	/// <summary>
	/// Functor to find if there is a transition registered for a result from a 
	///			particular sub state 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<class T>
	struct FindSuperStateTransition {
		FindSuperStateTransition(unsigned int subStateId, unsigned int result) :
			m_subStateId(subStateId),
			m_result(result) {
		}

		bool operator ()(const CppSuperStateTransitionInfo<T>& ssInfo) const {
			return ssInfo.m_stateId == m_subStateId && ssInfo.m_result == m_result;
		}


		unsigned int m_subStateId;	///< SubState of origine.
		unsigned int m_result;		///< End result code from sub state.
	};


}