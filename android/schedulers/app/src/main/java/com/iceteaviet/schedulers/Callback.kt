package com.iceteaviet.schedulers

interface Callback<T> {
    fun callback(result: T)
}