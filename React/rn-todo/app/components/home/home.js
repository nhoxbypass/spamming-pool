import React, { Component } from 'react';
import {
    View,
    Text
} from 'react-native';
import TodoListView from './todolistview.js'

export default class Home extends Component {
    constructor(props) {
        super(props);
        this.state = {
            data: this.data
        }
    }

    render() {
        return (
            <View style={{backgroundColor: 'white'}}>
                <TodoListView
                    data={this.state.data} />
            </View>
        )
    }

    static navigationOptions = {
        title: 'My Todo',
    }

    data = [
        { endTime: '16/02/2018', title: 'Homework' },
        { endTime: '22/12/2017', title: 'Workout' },
        { endTime: '12/10/2017', title: 'Sing' },
        { endTime: '12/10/2017', title: 'Hangout with friends' },
        { endTime: '12/10/2017', title: 'Sleep all day' },
    ];
}

module.exports = Home