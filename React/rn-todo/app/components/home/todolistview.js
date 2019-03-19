import React, { Component } from 'react';
import {
    View,
    FlatList,
    Text
} from 'react-native';
import TodoItemView from './todoitemview.js'
import styles from './styles';

export default class TodoListView extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <FlatList
                style={{ margin: 16 }}
                data={this.props.data} //Why not use state?
                keyExtractor={item => item.title}
                renderItem={this._renderItem}
            />
        )
    }

    _renderItem = ({ item, index }) => {
        return (
            <View>
                <TodoItemView {...item} />
                {(index !== this.props.data.length - 1) && this.renderSeparator()}
            </View>
        );
    }

    renderSeparator = () => {
        return (
            <View style={styles.blackLine}/>
        )
    }
}

module.exports = TodoListView