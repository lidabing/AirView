// Copyright (c) 2012 The AirView Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

cr.define('options', function() {
  const OptionsPage = options.OptionsPage;
  const ArrayDataModel = cr.ui.ArrayDataModel;

  /////////////////////////////////////////////////////////////////////////////
  // MouseGestureManager class:

  /**
   * Encapsulated handling of password and exceptions page.
   * @constructor
   */
  function MouseGestureManager() {
    OptionsPage.call(this,
                     'mousegesture',
                     'Mouse Gesture',
                     'mouse-gesture-manager-page');
  }

  cr.addSingletonGetter(MouseGestureManager);
  
  MouseGestureManager.prototype = {
  __proto__: OptionsPage.prototype,
  
   initializePage: function() {
      OptionsPage.prototype.initializePage.call(this);
      },
  };
  
      //[airview]
      //mgnList  ===>  Mouse Gesture name list
      //mgaList  ===>  Mouse Gesture Actions Name list
    MouseGestureManager.SetupMouseGestureActionsList= function (mgnList,mgaList) {
    var mgnCount = mgnList.length;
    $('mouse_gesture_actions_list').innerHTML = "";
     for (var i = 0; i < mgnCount; i++) {
             var mgn_item = mgnList[i];
			 var liEl = document.createElement('li');
			 var	iEl = document.createElement('i');
			 var spanEl = document.createElement('span');
			 var selectEl = document.createElement('select');
				iEl.style.backgroundPosition = mgn_item.backgroundPosition;
				liEl.appendChild(iEl);
				spanEl.innerHTML =mgn_item.name;
				liEl.appendChild(spanEl);
				//create select element
				selectELInner = "";
				for(var key in mgaList){
				var mga_item = mgaList[key];
				selected = (mga_item.id == mgn_item.selectid) ? 'selected' : '';
				selectELInner += '<option value="' + mga_item.id + '" ' + selected + '>' + mga_item.name + '</option>';
				}
				selectEl.innerHTML = selectELInner;
				selectEl.onchange = function(){
				var seleect_item_id = this.id.replace('MGSELECT_','');
				 chrome.send('setAirMouseGesture', [seleect_item_id,this.value]);
				}
						
				selectEl.id = 'MGSELECT_' + mgn_item.prefname;
				liEl.appendChild(selectEl);
				$('mouse_gesture_actions_list').appendChild(liEl);
     }
    };
    
    // Export
  return {
    MouseGestureManager: MouseGestureManager
  };
});