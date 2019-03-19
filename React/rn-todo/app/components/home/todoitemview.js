import React, { Component } from 'react';
import {
    View,
    Text,
    Image,
    TouchableOpacity
} from 'react-native';
import styles from './styles.js'

export default class TodoItemView extends Component {
    constructor(props) {
        super(props);
        this.state = {
            checked: false,
            selected: false
        }
    }

    render() {
        return (
            <TouchableOpacity
                onPress={() => this.setState({ selected: !this.state.selected })}>
                <View style={[styles.outerItemViewContainer, { elevation: this.state.selected ? 8 : 0 }]}>
                    <View style={styles.innerItemViewContainer}>
                        <View style={styles.circleView}>
                            <Text style={styles.priorityText}>HIGH</Text>
                        </View>
                        <View style={styles.content}>
                            <Text>{this.props.title}</Text>
                            <Text>{this.props.endTime}</Text>
                        </View>
                        <TouchableOpacity
                            onPress={() => this.setState({ checked: !this.state.checked })}>
                            <Image
                                style={styles.radioButton}
                                source={(this.state.checked) ? require('./../../res/images/ic_checkbox_fill.png') : require('./../../res/images/ic_checkbox.png')}>
                            </Image>
                        </TouchableOpacity>
                    </View >
                    {this._renderEditDelete()}
                </View>
            </TouchableOpacity>
        );
    }

    _renderEditDelete = () => {
        if (this.state.selected) {
            return (
                <View style={{ flex: 1, flexDirection: 'column', alignItems: 'center' }}>
                    <View style={styles.greyLine} />
                    <View style={[styles.innerItemViewContainer, { paddingBottom: 8 }]}>
                        <TouchableOpacity style={styles.innerItemViewContainer}>
                            <Image
                                style={[styles.icon, { tintColor: '#2196F3' }]}
                                source={require('./../../res/images/ic_edit.png')} />
                            <Text style={[styles.textCenter, { color: '#2196F3' }]}>UPDATE</Text>
                        </TouchableOpacity>

                        <TouchableOpacity style={styles.innerItemViewContainer}>
                            <Image
                                style={[styles.icon, { tintColor: '#F44336' }]}
                                source={require('./../../res/images/ic_delete.png')} />
                            <Text style={[styles.textCenter, { color: '#F44336' }]}>DELETE</Text>
                        </TouchableOpacity>
                    </View>
                </View>
            );
        } else {
            return null;
        }
    }
}

module.exports = TodoItemView