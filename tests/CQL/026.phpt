--TEST--
CommonMark\CQL firstChild(constrained)
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
paragraph
  * item
EOD
);

$call = new \CommonMark\CQL("/firstChild(List)");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\BulletList) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

