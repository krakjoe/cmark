--TEST--
CommonMark\CQL constraint Heading
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
## Heading
EOD
);

$call = new \CommonMark\CQL("/children(Heading)");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Heading) {
		echo "OK\n";
	} else  echo "FAIL\n";
});
?>
--EXPECT--
OK

