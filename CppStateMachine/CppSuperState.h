#pragma once

#include "CppState.h"
#include "CppSuperStateTransitionInfo.h"
#include "../CPPVariousUtils/Cpp_functors.h"
#include "../CPPVariousUtils/Cpp_pointerException.cpp"



///--------------------------------------------------------------------------------------
/// @file	CPPSuperState.h
/// @brief	Super State base class.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------


namespace CppStateMachine {

	///--------------------------------------------------------------------------------------
	///
	///	@brief	Pure base class for super states. Super states containt mr_states.
	///
	/// This class encapsulates 
	///
	/// There are three stages to a states life, On Entry, OnState and OnExit.
	///
	///--------------------------------------------------------------------------------------
	template <class T>
	class CPPSuperState : public mr_state<T> {
	private:
		typedef std::vector<CppSuperStateTransitionInfo<T> >	MR_SS_TRANSITION_VEC;	///< Transition vector.
		typedef typename MR_SS_TRANSITION_VEC::iterator			MR_SS_TRANSITION_IT;	///< Transition vector iterator.

	public:

		/// @brief	Constructor
		///
		///	@param	id	State ID.
		CPPSuperState(unsigned int id) : mr_state<T>(id) {
		}


		/// @brief	Destructor
		virtual ~CPPSuperState() {
			std::for_each(
				m_states.begin(), 
				m_states.end(), 
				CppUtils::DeletePtr<CppState>());
		}


		/// @brief	Pulse the state for it to execute its code.
		///
		/// @param	Tevent	The event to push at the state.
		///
		/// @return NULL if no state change required, otherwise the new state.
		virtual CppStateTransitionInfo<T> PulseState(const T& _event)
		{
			// Check for pre-emptive event at Super State level first.
			CppStateTransitionInfo<T> info = this->GetEventTransition(_event.m_id);
			if (info.m_type != NO_INFO) {
				return info;
			}

			// Excercise any super state OnState code.
			info = this->GetResultsTransition(this->OnState(_event));
			if (info.m_type != NO_INFO) {
				return info;
			}

			// Go to current sub state pulse.
			info = m_currentState->PulseState(_event);
			switch (info.m_type) {
			case NO_INFO:		return CppStateTransitionInfo<T>(_event.m_id, NO_INFO);
			case STATE_CHANGE:	return this->SetNextState(info);
			case SUBSTATE_EXIT:	return this->SetSSExitState(info);
			default:
				// TODO implement	
				//mr_utils::mr_exception::assertCondition(false, FL, L("Unhandled enum"));
			}

			return info;
		}


		/// @brief	Set the deafult state from the states registered. This will be the state
		///			on entry.
		///
		/// @exception	mr_utils::mr_pointerException if not found.
		///
		/// @param	id	The id of the state to set as default.
		void SetDefaultState(unsigned int id) {
			std::vector<CppState*>::iterator it =
				std::find_if(m_states.begin(), m_states.end(), FindSubState<T>(id));

			CppUtils::Cpp_exception::assertCondition(it != m_states.end(), FL, L("State not found"));
			CppUtils::Cpp_pointerException::ptrAssert(*it, FL);
			m_currentState = *it;
		}


		/// @brief	Add a new sub state.
		void AddState(CppState<T>* _state) {
			CppUtils::Cpp_pointerException::ptrAssert(_state, FL);
			CppUtils::Cpp_exception::assertCondition(
				std::find_if(m_states.begin(), m_states.end(), FindSubState<T>(_state->Id())) == m_states.end(),
				FL,
				L("State already registered")
			);
			m_states.push_back(_state);
		}


		virtual unsigned int OnState(const T& /*event*/)
		{
			// By default, the super state has no OnState code.
			return 0;
		}



	protected:

		virtual void OnEntry()
		{
			// TODO implement	
			//mr_utils::mr_pointerException::ptrAssert(m_defaultState, FL);
			m_currentState = m_defaultState;
			this->OnSSEntry();
			m_currentState->OnEntry();
		}


		virtual void OnExit()
		{
			this->OnSSExit();
			m_currentState->OnExit();
		}

	private:

		std::vector<CppState*>	m_states;
		CppState* m_defaultState;
		CppState* m_currentState;

		MR_SS_TRANSITION_VEC	m_ssTransitions;	///< Bridge between sub and super state transitions.


		virtual void OnSSEntry() {
		}


		virtual void OnSSExit() {
		}


		CppStateTransitionInfo<T> SetNextState(const CppStateTransitionInfo<T>& info) {
			m_currentState->OnExit();

			//mr_utils::mr_pointerException::ptrAssert(info.m_nextState, FL);
			m_currentState = info.m_nextState;
			m_currentState->OnEntry();
			return CppStateTransitionInfo<T>(info.m_id, NO_INFO);
		}


		/// @brief	Return the appropriate next state from the super state's list
		///			of Results Transitions.
		CppStateTransitionInfo<T> SetSSExitState(const CppStateTransitionInfo<T>& info)
		{
			// The result returned from the sub state must also be registered
			// with the superstate. It is the super state that has the state* registered.
			MR_SS_TRANSITION_IT it =
				std::find_if(
					m_ssTransitions.begin(),
					m_ssTransitions.end(),
					FindSuperStateTransition<T>(m_currentState->Id(), info.m_id)
				);

			//mr_utils::mr_exception::assertCondition(it != m_ssTransitions.end(), FL, L("No transition"));
			//mr_utils::mr_pointerException::ptrAssert(it->m_nextState, FL);

			return CppStateTransitionInfo<T>(it->m_result, STATE_CHANGE, it->m_nextState);
		}

	};


	//----------------------------------------------------------
	/// @Functor to find the state from the list of those registered.
	template<class T> struct FindSubState {
		
		FindSubState(unsigned int id) : m_id(id) {
		}

		bool operator ()(const mr_state<T>* _state) const {
			return _state->Id() == m_id;
		}

		unsigned int m_id; ///< State id to locate.
	};





}