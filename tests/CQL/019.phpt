--TEST--
CommonMark\CQL constraint HTMLInline
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
html goes <inline/> too
EOD
);

$call = new \CommonMark\CQL("/children(Paragraph)[/children(HTMLInline)]");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\HTMLInline) {
		echo "OK";
	} else  echo "FAIL";
});
?>
--EXPECT--
OK

