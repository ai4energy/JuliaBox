import QtQuick
import QtQuick.Controls
import org.julialang

ApplicationWindow {
  title: "Test"
  visible: true
  Grid {
    rows: 5
    columns: 1
    Repeater {
      model: slider
      delegate: Row {
        Slider {
          id: sliderControl
          from: 0.0
          to: 2.0
          onValueChanged: {
            sliderval = value;
          }

          Component.onCompleted: {
            value = sliderval;
          }
          Connections {
		        target: slider
		        function onDataChanged() { sliderControl.value = sliderval; }
	        }
        }
      }
    }
  }
}