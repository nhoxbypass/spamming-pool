import React from 'react'
import {
    StyleSheet,
    Image
} from 'react-native'

export default styles = StyleSheet.create({
    outerItemViewContainer: {
        marginBottom: 8,
        alignItems: 'center',
        backgroundColor: 'white'
    },
    innerItemViewContainer: {
        flexDirection: 'row',
        flex: 1,
        justifyContent: 'center'
    },
    radioButton: {
        flex: 1,
        width: 24,
        height: 24,
        resizeMode: Image.resizeMode.contain,
    },
    priorityText: {
        textAlign: 'center', 
        color: 'white',
        fontSize: 12
    },
    circleView: {
        backgroundColor: 'red',
        width: 40,
        height: 40,
        borderRadius: 40 / 2,
        justifyContent: 'center',
        alignItems: 'center'
    },
    content: {
        flex: 6,
        marginLeft: 16,
        marginRight: 16
    },
    blackLine: {
        height: 1,
        backgroundColor: '#9E9E9E',
        marginBottom: 8,
        marginLeft: 56
    },
    greyLine: {
        height: 1,
        width: 2048,
        marginTop: 8,
        marginBottom: 8,
        backgroundColor: '#E0E0E0'
    },
    textCenter: {
        textAlignVertical: 'center'
    },
    icon: {
        width: 24,
        height: 24,
        marginRight: 16
    }
});