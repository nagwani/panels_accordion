<?php


/**
 * @file
 * Definition of the collapsible panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('Accordion'),
  'description' => t('Allows the panel pane to be collapsed.'),
  'render region' => 'panels_accordion_render_region',
  'render pane' => 'panels_accordion_render_pane',
  'settings form' => 'panels_accordion_region_settings_form',
  'pane settings form' => 'panels_accordion_pane_settings_form',
);

/**
 * Settings form callback for region settings.
 */
function panels_accordion_region_settings_form($style_settings) {
  $form = array();

  $animated_options = array(
      'none' => t('None'),
      'slide' => t('Slide'),
      'swing' => t('Swing'),
      'linear' => t('Linear'),
      'easeInQuart' => t('easeInQuart'),
      'easeOutQuart' => t('easeOutQuart'),
      'easeInOutQuart' => t('easeInOutQuart'),
      'easeInExpo' => t('easeInExpo'),
      'easeOutExpo' => t('easeOutExpo'),
      'easeInOutExpo' => t('easeInOutExpo'),
      'easeInBack' => t('easeInBack'),
      'easeOutBack' => t('easeOutBack'),
      'easeInOutBack' => t('easeInOutBack'),
      'easeInQuad' => t('easeInQuad'),
      'easeOutQuad' => t('easeOutQuad'),
      'easeInOutQuad' => t('easeInOutQuad'),
      'easeInQuint' => t('easeInQuint'),
      'easeOutQuint' => t('easeOutQuint'),
      'easeInOutQuint' => t('easeInOutQuint'),
      'easeInCirc' => t('easeInCirc'),
      'easeOutCirc' => t('easeOutCirc'),
      'easeInOutCirc' => t('easeInOutCirc'),
      'easeInBounce' => t('easeInBounce'),
      'easeOutBounce' => t('easeOutBounce'),
      'easeInOutBounce' => t('easeInOutBounce'),
      'easeInCubic' => t('easeInCubic'),
      'easeOutCubic' => t('easeOutCubic'),
      'easeInOutCubic' => t('easeInOutCubic'),
      'easeInSine' => t('easeInSine'),
      'easeOutSine' => t('easeOutSine'),
      'easeInOutSine' => t('easeInOutSine'),
      'easeInElastic' => t('easeInElastic'),
      'easeOutElastic' => t('easeOutElastic'),
      'easeInOutElastic' => t('easeInOutElastic'),
    );

  $form['region_accordion_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Accordion Id'),
    '#description' => t('Accordion ID to be used. Please use machine name format.'),
    '#required' => TRUE,
    '#default_value' => (isset($style_settings['region_accordion_id'])) ? $style_settings['region_accordion_id'] : ''
  );

  $form['description'] = array(
    '#type' => 'markup',
    '#value' => 'See <a href="http://docs.jquery.com/UI/Accordion">http://docs.jquery.com/UI/Accordion</a> for a list of possible values for these options',
  );

  // http://docs.jquery.com/UI/Accordion for how to implement these attributes
  $form['active'] = array(
    '#type' => 'textfield',
    '#title' => t('active'),
    '#default_value' => isset($style_settings['active']) ? $style_settings['active'] : $style_settings['active'] = 0,
    '#description' => t('Selector for the active element. Set to false to display none at start. Needs collapsible: true.'),
  );

  $form['collapsible'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow for all rows to be closed'),
      '#default_value' => $style_settings['collapsible'],
      '#description' => t('If you check this on, when the user clicks on an opened item, it will close.'),
    );

  $form['animated'] = array(
      '#type' => 'select',
      '#title' => t('Animation effect'),
      '#default_value' => $style_settings['animated'],
      '#description' => t('Choose what animation effect you would like to see, or "None" to disable it.'),
      '#options' => $animated_options,
    );

  $form['autoHeight'] = array(
    '#type' => 'radios',
    '#title' => t('autoHeight'),
    '#options' => array('true' => t('true'), 'false' => t('false')),
    '#default_value' => isset($style_settings['autoHeight']) ? $style_settings['autoHeight'] : $style_settings['autoHeight'] = 'false',
    '#description' => t('If set, the highest content part is used as height reference for all other parts. Provides more consistent animations.'),
  );
  return $form;
}

/**
 * Settings form callback for pane settings.
 */
function panels_accordion_pane_settings_form($style_settings) {
  $form = array();
  $form['pane_collapsed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Collapsed by default'),
    '#default_value' => (isset($style_settings['pane_collapsed'])) ? $style_settings['pane_collapsed'] : FALSE
  );
  return $form;
}

/**
 * Render callback for regions.
 *
 * @ingroup themeable
 */
function theme_panels_accordion_render_region($vars) {
  $settings = $vars['settings'];
  $panes = $vars['panes'];
  $display = $vars['display'];

  $content = implode('', $vars['panes']);
  jquery_ui_add('ui.accordion');
  jquery_ui_add('effects.core');

  drupal_add_css(drupal_get_path('module', 'jquery_ui').'/jquery.ui/themes/base/ui.accordion.css');

  foreach($settings as $key=>$val){
    // if it's a string, convert slide to 'slide' (necessary as per http://docs.jquery.com/UI/Accordion).
    $val = is_numeric($val) ? $val: "'$val'" ;
    $options[] = $key. ':' .$val;
  }
  $options = '{' .implode(',', $options). '}';
  // if it's 'true'/'false', convert it back to true/false.
  $options = str_replace(array("'false'", "'true'"), array("false", "true"), $options);

  drupal_add_js('
    jQuery(document).ready(function($){
      $(\'#'. $settings['region_accordion_id'] .'\').accordion(' . $options . ');
    });', 'inline');

  if (empty($settings['region_title'])) {
    $settings['region_title'] = '<empty>';
  }
  if (empty($settings['region_collapsed'])) {
    $settings['region_collapsed'] = FALSE;
  }
  $title = ctools_context_keyword_substitute($settings['region_title'], array(), $vars['display']->context);
  $output = theme('panels_accordion_region', array('handle' => $title, 'content' => $content, 'accordion_id' => $settings['region_accordion_id']));
  return $output;
}

/**
 * Render callback for panes.
 *
 * @ingroup themeable
 */
function theme_panels_accordion_render_pane($vars) {

  $content = $vars['content'];
  $pane = $vars['pane'];
  $display = $vars['display'];
  $settings = $vars['settings'];

  if (empty($content->content)) {
    return;
  }

  if ($content->content != '') {
    if (is_array($content->content)) {
      $content->content = drupal_render($content->content);
    }

    $output = theme('panels_accordion_pane', array('handle' => $content->title, 'content' => $content->content, 'collapsed' => $settings['pane_collapsed'], 'pane' => $pane));
  }
  else {
    $output = theme('panels_pane', array('content' => $content, 'pane' => $pane, 'display' => $display));
  }

  return $output;
}

/**
 * Render callback for panes.
 *
 * @ingroup themeable
 */
function theme_panels_accordion_pane($vars) {

  $pane_css = $pane_id = '';
  if (isset($vars['pane']) && is_object($vars['pane'])) {
    $pane_css = $vars['pane']->css;
    $pane_id = !empty($pane_css['css_id']) ? ' id="' . $pane_css['css_id'] . '"' : '';
    $pane_css = !empty($pane_css['css_class']) ? ' ' . $pane_css['css_class'] : '';
  }

  $output = '<h3>' . check_plain($vars['handle']) . '</h3>';
  $output .= $vars['content'];

  return $output;
}

/**
 * Render callback for region.
 *
 * @ingroup themeable
 */
function theme_panels_accordion_region($vars) {

  $pane_id = $vars['accordion_id'];

  $output = '<div id="' . $pane_id  . '"">';
  $output .= $vars['content'];
  return $output;
}
