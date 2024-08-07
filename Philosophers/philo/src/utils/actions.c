/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwintgen <rwintgen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:27:50 by rwintgen          #+#    #+#             */
/*   Updated: 2024/07/01 15:28:02 by rwintgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Set of helper functions to conveniently call pthread functions.
// Used for threads, mutexes and error management

static void	thr_msg_if_err(int err, t_action action);
static void	mtx_msg_if_err(int err, t_action action);

void	thread_action(pthread_t *thread, void *(*func)(void *), \
					void *data, t_action action)
{
	if (action == CREATE)
		thr_msg_if_err(pthread_create(thread, NULL, func, data), action);
	else if (action == JOIN)
		thr_msg_if_err(pthread_join(*thread, NULL), action);
	else if (action == DETACH)
		thr_msg_if_err(pthread_detach(*thread), action);
	else
		err_msg(E_THR_ACTION, MSG_THR_ACTION);
}

void	mutex_action(pthread_mutex_t *mutex, t_action action)
{
	if (action == LOCK)
		mtx_msg_if_err(pthread_mutex_lock(mutex), action);
	else if (action == UNLOCK)
		mtx_msg_if_err(pthread_mutex_unlock(mutex), action);
	else if (action == INIT)
		mtx_msg_if_err(pthread_mutex_init(mutex, NULL), action);
	else if (action == DESTROY)
		mtx_msg_if_err(pthread_mutex_destroy(mutex), action);
	else
		err_msg(E_MTX_ACTION, MSG_MTX_ACTION);
}

static void	thr_msg_if_err(int err, t_action action)
{
	if (err == EAGAIN)
		err_msg(E_THR_AGAIN, MSG_THR_AGAIN);
	else if (err == EPERM)
		err_msg(E_THR_PERM, MSG_THR_PERM);
	else if (err == EINVAL && action == CREATE)
		err_msg(E_THR_ATTR_VAL, MSG_THR_ATTR_VAL);
	else if (err == EINVAL && (action == JOIN || action == DETACH))
		err_msg(E_THR_VAL, MSG_THR_VAL);
	else if (err == ESRCH)
		err_msg(E_THR_SRCH, MSG_THR_SRCH);
	else if (err == EDEADLK)
		err_msg(E_THR_DDLK, MSG_THR_DDLK);
}

static void	mtx_msg_if_err(int err, t_action action)
{
	if (err == EINVAL)
	{
		if (action == INIT)
			err_msg(E_MTX_ATTR_VAL, MSG_MTX_ATTR_VAL);
		else if (action < INIT)
			err_msg(E_MTX_VAL, MSG_MTX_VAL);
	}
	else if (err == EDEADLK)
		err_msg(E_MTX_DDLK, MSG_MTX_DDLK);
	else if (err == EPERM)
		err_msg(E_MTX_PERM, MSG_MTX_PERM);
	else if (err == ENOMEM)
		err_msg(E_MTX_MEM, MSG_MTX_MEM);
	else if (err == EBUSY)
		err_msg(E_MTX_BUSY, MSG_MTX_BUSY);
}
